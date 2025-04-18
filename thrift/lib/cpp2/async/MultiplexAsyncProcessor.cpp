/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <thrift/lib/cpp2/async/MultiplexAsyncProcessor.h>

#include <optional>
#include <string_view>

#include <folly/GLog.h>
#include <folly/Overload.h>
#include <folly/container/F14Map.h>
#include <folly/container/F14Set.h>

#include <thrift/lib/cpp2/async/AsyncProcessorHelper.h>

namespace apache::thrift {

namespace {

std::optional<std::string_view> getInteractionNameFromMethodName(
    std::string_view methodName) {
  // Interaction methods are formatted like "{interaction_name}.{method_name}"
  auto separator = methodName.find('.');
  if (separator == std::string_view::npos) {
    return std::nullopt;
  }
  return methodName.substr(0, separator);
}

struct MetadataImpl final : public AsyncProcessorFactory::MethodMetadata {
  // Index of the AsyncProcessor to route this method to
  std::size_t sourceIndex;
  // The underlying metadata produced by the AsyncProcessorFactory at
  // sourceIndex
  std::shared_ptr<const AsyncProcessorFactory::MethodMetadata> inner;

  explicit MetadataImpl(
      std::size_t sourceIndex,
      std::shared_ptr<const AsyncProcessorFactory::MethodMetadata>&& inner)
      : sourceIndex(sourceIndex), inner(std::move(inner)) {}
};

MultiplexAsyncProcessorFactory::CompositionMetadata computeCompositionMetadata(
    const std::vector<std::shared_ptr<AsyncProcessorFactory>>&
        processorFactories) {
  MultiplexAsyncProcessorFactory::CompositionMetadata compositionMetadata;

  AsyncProcessorFactory::MethodMetadataMap knownMethods;
  folly::F14FastSet<std::string> seenInteractions;
  auto addToKnownMethods =
      [&](AsyncProcessorFactory::MethodMetadataMap& metadataMap,
          std::size_t sourceIndex) {
        folly::F14FastSet<std::string_view> newlySeenInteractions;
        for (auto& [name, metadata] : metadataMap) {
          if (auto interactionName = getInteractionNameFromMethodName(name)) {
            if (seenInteractions.contains(*interactionName)) {
              // The interaction defined earlier gets precedence and no methods
              // should be added for it from a later AsyncProcessorFactory. This
              // prevents the latter interaction from being ever created.
              continue;
            }
            newlySeenInteractions.emplace(*interactionName);
          }
          // Note that emplace does NOT replace existing entries - methods
          // from earlier AsyncProcessorFactory's always take precedence.
          knownMethods.emplace(
              name,
              std::make_shared<MetadataImpl>(sourceIndex, std::move(metadata)));
        }
        auto oldSize = seenInteractions.size();
        (void)oldSize;
        seenInteractions.insert(
            newlySeenInteractions.begin(), newlySeenInteractions.end());
        // If we implemented it right, seenInteractions and
        // newlySeenInteractions should be distinct
        DCHECK(
            seenInteractions.size() == oldSize + newlySeenInteractions.size());
      };

  for (std::size_t sourceIndex = 0; sourceIndex < processorFactories.size();
       ++sourceIndex) {
    auto metadataResult =
        processorFactories[sourceIndex]->createMethodMetadata();
    auto* metadataMap =
        std::get_if<AsyncProcessorFactory::MethodMetadataMap>(&metadataResult);
    if (metadataMap == nullptr) {
      // Per our contract, the first wildcard-like processor will swallow up all
      // methods that are not explicitly named in knownMethods by a preceding
      // processor. So, as long as we keep track of the first such processor, we
      // can route all wildcard methods to it in constant time.
      if (auto* wildcardMetadataMap =
              std::get_if<AsyncProcessorFactory::WildcardMethodMetadataMap>(
                  &metadataResult)) {
        addToKnownMethods(wildcardMetadataMap->knownMethods, sourceIndex);
        compositionMetadata.firstWildcardLike =
            MultiplexAsyncProcessorFactory::CompositionMetadata::Wildcard{
                sourceIndex};
      } else {
        DCHECK(std::holds_alternative<
               AsyncProcessorFactory::MetadataNotImplemented>(metadataResult));
        compositionMetadata.firstWildcardLike = MultiplexAsyncProcessorFactory::
            CompositionMetadata::WildcardNoMetadata{sourceIndex};
      }
      break;
    }
    addToKnownMethods(*metadataMap, sourceIndex);
  }

  compositionMetadata.cachedMethodMetadataResult =
      [&]() -> AsyncProcessorFactory::CreateMethodMetadataResult {
    if (compositionMetadata.wildcardIndex().has_value()) {
      return AsyncProcessorFactory::WildcardMethodMetadataMap{
          std::move(knownMethods)};
    }
    return std::move(knownMethods);
  }();

  return compositionMetadata;
}

class MultiplexAsyncProcessor final : public AsyncProcessor {
 public:
  void processSerializedRequest(
      ResponseChannelRequest::UniquePtr,
      SerializedRequest&&,
      protocol::PROTOCOL_TYPES,
      Cpp2RequestContext*,
      folly::EventBase*,
      concurrency::ThreadManager*) override {
    LOG(FATAL)
        << "This method should never be called since we implement createMethodMetadata()";
  }

  void processSerializedCompressedRequestWithMetadata(
      ResponseChannelRequest::UniquePtr req,
      SerializedCompressedRequest&& serializedRequest,
      const MethodMetadata& untypedMethodMetadata,
      protocol::PROTOCOL_TYPES protocolType,
      Cpp2RequestContext* context,
      folly::EventBase* eb,
      concurrency::ThreadManager* tm) override {
    auto maybeTrackInteraction = [&](AsyncProcessor& processor) {
      if (defaultInteractionProcessor_ == nullptr) {
        // The first to create an interaction gets the privilege of being the
        // "default"
        defaultInteractionProcessor_ = &processor;
        return;
      }
      if (&processor == defaultInteractionProcessor_) {
        return;
      }
      if (auto interactionCreate = context->getInteractionCreate();
          interactionCreate.has_value() &&
          *interactionCreate->interactionId_ref() > 0) {
        // Note that when there is a duplicate interaction we do not replace the
        // existing entry. A connection should have unique interaction IDs which
        // means that the underlying processor should fail (and close the
        // connection) - it's safe to ignore the duplicated ID.
        inflightInteractions_.emplace(
            *interactionCreate->interactionId_ref(), &processor);
      }
    };

    if (auto* methodMetadata =
            AsyncProcessorHelper::metadataOfType<MetadataImpl>(
                untypedMethodMetadata)) {
      DCHECK(methodMetadata->sourceIndex < processors_.size());
      auto& processor = *processors_[methodMetadata->sourceIndex];
      maybeTrackInteraction(processor);
      processor.processSerializedCompressedRequestWithMetadata(
          std::move(req),
          std::move(serializedRequest),
          *methodMetadata->inner,
          protocolType,
          context,
          eb,
          tm);
      return;
    }

    if (auto* wildcardMethodMetadata = AsyncProcessorHelper::metadataOfType<
            AsyncProcessorFactory::WildcardMethodMetadata>(
            untypedMethodMetadata)) {
      folly::variant_match(
          compositionMetadata_.firstWildcardLike,
          [](std::monostate) {
            LOG(FATAL)
                << "Received WildcardMethodMetadata but expected no WildcardMethodMetadataMap was composed";
          },
          [&](const MultiplexAsyncProcessorFactory::CompositionMetadata::
                  Wildcard& wildcard) {
            DCHECK(wildcard.index < processors_.size());
            auto& processor = *processors_[wildcard.index];
            maybeTrackInteraction(processor);
            processor.processSerializedCompressedRequestWithMetadata(
                std::move(req),
                std::move(serializedRequest),
                *wildcardMethodMetadata,
                protocolType,
                context,
                eb,
                tm);
          },
          [&](const MultiplexAsyncProcessorFactory::CompositionMetadata::
                  WildcardNoMetadata& wildcard) {
            DCHECK(wildcard.index < processors_.size());
            auto& processor = *processors_[wildcard.index];
            maybeTrackInteraction(processor);
            processor.processSerializedCompressedRequest(
                std::move(req),
                std::move(serializedRequest),
                protocolType,
                context,
                eb,
                tm);
          });
      return;
    }

    LOG(FATAL) << "Received metadata of unknown type";
  }

  void getServiceMetadata(
      metadata::ThriftServiceMetadataResponse& actualResponse) override {
    auto copyMetadataInto =
        [](metadata::ThriftMetadata& dst,
           const metadata::ThriftServiceMetadataResponse& src) {
          // The multiplexed services makes reference to a composed service, so
          // we need to include it in the metadata.
          auto& metadata = *src.metadata_ref();
          dst.enums_ref()->insert(
              metadata.enums_ref()->begin(), metadata.enums_ref()->end());
          dst.structs_ref()->insert(
              metadata.structs_ref()->begin(), metadata.structs_ref()->end());
          dst.exceptions_ref()->insert(
              metadata.exceptions_ref()->begin(),
              metadata.exceptions_ref()->end());
          dst.services_ref()->insert(
              metadata.services_ref()->begin(), metadata.services_ref()->end());
        };

    for (auto& processor : processors_) {
      metadata::ThriftServiceMetadataResponse response;
      processor->getServiceMetadata(response);
      // Copying gives precedence to earlier inserted entries - this matches
      // the semantics of the processor method delegation.
      copyMetadataInto(*actualResponse.metadata_ref(), response);

      actualResponse.services_ref()->insert(
          actualResponse.services_ref()->end(),
          response.services_ref()->begin(),
          response.services_ref()->end());
    }

    // TODO(praihan): Remove context field from metadata response object
    // There is no "correct" way to set context for MultiplexAsyncProcessor. Our
    // best guess would be the first service, which is likely to be most
    // relevant to the user.
    DCHECK(!actualResponse.services_ref()->empty());
    const auto& defaultServiceContextRef =
        actualResponse.services_ref()->front();
    actualResponse.context_ref()->service_info_ref() =
        actualResponse.metadata_ref()->services_ref()->at(
            *defaultServiceContextRef.service_name_ref());
    actualResponse.context_ref()->module_ref() =
        *defaultServiceContextRef.module_ref();
  }

  void terminateInteraction(
      int64_t id,
      Cpp2ConnContext& ctx,
      folly::EventBase& eb) noexcept override {
    AsyncProcessor* processor = nullptr;
    if (auto foundProcessor = folly::get_ptr(inflightInteractions_, id)) {
      processor = *foundProcessor;
    } else {
      // The first processor serves the niche of being the "default" interaction
      // creator. We don't put its IDs in the map.
      processor = defaultInteractionProcessor_;
    }
    if (processor != nullptr) {
      processor->terminateInteraction(id, ctx, eb);
    }
  }

  void destroyAllInteractions(
      Cpp2ConnContext& ctx, folly::EventBase& eb) noexcept override {
    inflightInteractions_.clear();
    for (auto& processor : processors_) {
      processor->destroyAllInteractions(ctx, eb);
    }
  }

  explicit MultiplexAsyncProcessor(
      std::vector<std::unique_ptr<AsyncProcessor>>&& processors,
      const MultiplexAsyncProcessorFactory::CompositionMetadata&
          compositionMetadata)
      : processors_(std::move(processors)),
        compositionMetadata_(compositionMetadata) {
    DCHECK(!processors_.empty());
  }

 private:
  const std::vector<std::unique_ptr<AsyncProcessor>> processors_;
  const MultiplexAsyncProcessorFactory::CompositionMetadata&
      compositionMetadata_;
  folly::F14FastMap<std::int64_t, AsyncProcessor*> inflightInteractions_;
  // The "default" processor is expected to consume a disproportionately large
  // chunk of the traffic. To save memory, we avoid tracking interactions in the
  // map for the first processor that creates an interaction.
  AsyncProcessor* defaultInteractionProcessor_{nullptr};
};

} // namespace

MultiplexAsyncProcessorFactory::MultiplexAsyncProcessorFactory(
    std::vector<std::shared_ptr<AsyncProcessorFactory>> processorFactories)
    : processorFactories_(std::move(processorFactories)),
      compositionMetadata_(computeCompositionMetadata(processorFactories_)) {
  CHECK(!processorFactories_.empty());
}

std::unique_ptr<AsyncProcessor> MultiplexAsyncProcessorFactory::getProcessor() {
  std::vector<std::unique_ptr<AsyncProcessor>> processors;
  processors.reserve(processorFactories_.size());
  for (auto& processorFactory : processorFactories_) {
    processors.emplace_back(processorFactory->getProcessor());
  }
  return std::make_unique<MultiplexAsyncProcessor>(
      std::move(processors), compositionMetadata_);
}

AsyncProcessorFactory::CreateMethodMetadataResult
MultiplexAsyncProcessorFactory::createMethodMetadata() {
  return compositionMetadata_.cachedMethodMetadataResult;
}

std::shared_ptr<folly::RequestContext>
MultiplexAsyncProcessorFactory::getBaseContextForRequest(
    const MethodMetadata& untypedMethodMetadata) {
  if (auto* methodMetadata = AsyncProcessorHelper::metadataOfType<MetadataImpl>(
          untypedMethodMetadata)) {
    return processorFactories_[methodMetadata->sourceIndex]
        ->getBaseContextForRequest(*methodMetadata->inner);
  }

  if (auto* wildcardMethodMetadata = AsyncProcessorHelper::metadataOfType<
          AsyncProcessorFactory::WildcardMethodMetadata>(
          untypedMethodMetadata)) {
    auto wildcardIndex = compositionMetadata_.wildcardIndex();
    DCHECK(wildcardIndex.has_value())
        << "Received WildcardMethodMetadata but expected no WildcardMethodMetadataMap was composed";
    return processorFactories_[*wildcardIndex]->getBaseContextForRequest(
        *wildcardMethodMetadata);
  }

  LOG(FATAL) << "Received metadata of unknown type";
  return nullptr;
}

std::vector<ServiceHandler*>
MultiplexAsyncProcessorFactory::getServiceHandlers() {
  std::vector<ServiceHandler*> result;
  for (auto& processorFactory : processorFactories_) {
    auto newHandlers = processorFactory->getServiceHandlers();
    result.insert(result.end(), newHandlers.begin(), newHandlers.end());
  }
  return result;
}

std::optional<std::size_t>
MultiplexAsyncProcessorFactory::CompositionMetadata::wildcardIndex() const {
  using Result = std::optional<std::size_t>;
  return folly::variant_match(
      firstWildcardLike,
      [](std::monostate) -> Result { return std::nullopt; },
      [](auto&& wildcard) -> Result { return wildcard.index; });
}

} // namespace apache::thrift
