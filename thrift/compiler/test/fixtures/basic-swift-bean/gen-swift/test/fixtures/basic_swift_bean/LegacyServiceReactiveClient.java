/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

package test.fixtures.basic_swift_bean;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;
import org.apache.thrift.protocol.*;
import org.apache.thrift.InteractionCreate;
import com.facebook.thrift.client.ResponseWrapper;
import com.facebook.thrift.client.RpcOptions;


public class LegacyServiceReactiveClient 
  implements LegacyService.Reactive {
  private final org.apache.thrift.ProtocolId _protocolId;
  private final reactor.core.publisher.Mono<? extends com.facebook.thrift.client.RpcClient> _rpcClient;
  private final Map<String, String> _headers;
  private final Map<String, String> _persistentHeaders;
  private final AtomicLong _interactionCounter;
  private final Set<Long> _activeInteractions;

  private static final TField _getPoints_KEY_FIELD_DESC = new TField("key", TType.SET, (short)1);
  private static final TField _getPoints_LEGACY_STUFF_FIELD_DESC = new TField("legacyStuff", TType.I64, (short)-1);
  private static final java.util.Map<Short, com.facebook.thrift.payload.Reader> _getPoints_EXCEPTION_READERS = java.util.Collections.emptyMap();

  static {
  }

  public LegacyServiceReactiveClient(org.apache.thrift.ProtocolId _protocolId, reactor.core.publisher.Mono<? extends com.facebook.thrift.client.RpcClient> _rpcClient) {
    
    this._protocolId = _protocolId;
    this._rpcClient = _rpcClient;
    this._headers = java.util.Collections.emptyMap();
    this._persistentHeaders = java.util.Collections.emptyMap();
    this._interactionCounter = new AtomicLong(0);
    this._activeInteractions = ConcurrentHashMap.newKeySet();
  }

  public LegacyServiceReactiveClient(org.apache.thrift.ProtocolId _protocolId, reactor.core.publisher.Mono<? extends com.facebook.thrift.client.RpcClient> _rpcClient, Map<String, String> _headers, Map<String, String> _persistentHeaders) {
    this(_protocolId, _rpcClient, _headers, _persistentHeaders, new AtomicLong(), ConcurrentHashMap.newKeySet());
  }

  public LegacyServiceReactiveClient(org.apache.thrift.ProtocolId _protocolId, reactor.core.publisher.Mono<? extends com.facebook.thrift.client.RpcClient> _rpcClient, Map<String, String> _headers, Map<String, String> _persistentHeaders, AtomicLong interactionCounter, Set<Long> activeInteractions) {
    
    this._protocolId = _protocolId;
    this._rpcClient = _rpcClient;
    this._headers = _headers;
    this._persistentHeaders = _persistentHeaders;
    this._interactionCounter = interactionCounter;
    this._activeInteractions = activeInteractions;
  }

  @java.lang.Override
  public void dispose() {}

  private com.facebook.thrift.payload.Writer _creategetPointsWriter(final Set<String> key, final long legacyStuff) {
    return oprot -> {
      try {
        {
          oprot.writeFieldBegin(_getPoints_KEY_FIELD_DESC);

          Set<String> _iter0 = key;

          oprot.writeSetBegin(new TSet(TType.STRING, _iter0.size()));
        for (String _iter1 : _iter0) {
          oprot.writeString(_iter1);
        }
        oprot.writeSetEnd();
          oprot.writeFieldEnd();
        }

        {
          oprot.writeFieldBegin(_getPoints_LEGACY_STUFF_FIELD_DESC);

          long _iter0 = legacyStuff;

          oprot.writeI64(legacyStuff);
          oprot.writeFieldEnd();
        }


      } catch (Throwable _e) {
        throw reactor.core.Exceptions.propagate(_e);
      }
    };
  }

  private static final com.facebook.thrift.payload.Reader _getPoints_READER =
    oprot -> {
              try {
                Map<String, List<Integer>> _r;
            {
            TMap _map = oprot.readMapBegin();
            _r = new HashMap<String, List<Integer>>(Math.max(0, _map.size));
            for (int _i = 0; (_map.size < 0) ? oprot.peekMap() : (_i < _map.size); _i++) {
                
                String _key1 = oprot.readString();
                List<Integer> _value1;
            {
            TList _list1 = oprot.readListBegin();
            _value1 = new ArrayList<Integer>(Math.max(0, _list1.size));
            for (int _i1 = 0; (_list1.size < 0) ? oprot.peekList() : (_i1 < _list1.size); _i1++) {
                
                
                int _value2 = oprot.readI32();
                
                
                _value1.add(_value2);
                
            }
            oprot.readListEnd();
            }

                _r.put(_key1, _value1);
            }
            }
            oprot.readMapEnd();
                return _r;


              } catch (Throwable _e) {
                throw reactor.core.Exceptions.propagate(_e);
              }
            };


  @java.lang.Override
  public reactor.core.publisher.Mono<com.facebook.thrift.client.ResponseWrapper<Map<String, List<Integer>>>> getPointsWrapper(final Set<String> key, final long legacyStuff,  final com.facebook.thrift.client.RpcOptions rpcOptions) {
    return _rpcClient
      .flatMap(_rpc -> {
        org.apache.thrift.RequestRpcMetadata _metadata = new org.apache.thrift.RequestRpcMetadata.Builder()
                .setName("getPoints")
                .setKind(org.apache.thrift.RpcKind.SINGLE_REQUEST_SINGLE_RESPONSE)
                .setOtherMetadata(getHeaders(rpcOptions))
                .setProtocol(_protocolId)
                .build();

            com.facebook.thrift.payload.ClientRequestPayload<Map<String, List<Integer>>> _crp =
                com.facebook.thrift.payload.ClientRequestPayload.create(
                    _creategetPointsWriter(key, legacyStuff),
                    _getPoints_READER,
                    _getPoints_EXCEPTION_READERS,
                    _metadata,
                    java.util.Collections.emptyMap());

            return _rpc
                .singleRequestSingleResponse(_crp, rpcOptions).doOnNext(_p -> {if(_p.getException() != null) throw reactor.core.Exceptions.propagate(_p.getException());});
      });
  }

  @java.lang.Override
  public reactor.core.publisher.Mono<Map<String, List<Integer>>> getPoints(final Set<String> key, final long legacyStuff,  final com.facebook.thrift.client.RpcOptions rpcOptions) {
    return getPointsWrapper(key, legacyStuff,  rpcOptions).map(_p -> _p.getData());
  }

  @java.lang.Override
  public reactor.core.publisher.Mono<Map<String, List<Integer>>> getPoints(final Set<String> key, final long legacyStuff) {
    return getPoints(key, legacyStuff,  com.facebook.thrift.client.RpcOptions.EMPTY);
  }



  private Map<String, String> getHeaders(com.facebook.thrift.client.RpcOptions rpcOptions) {
      Map<String, String> headers = new HashMap<>();
      if (rpcOptions.getRequestHeaders() != null && !rpcOptions.getRequestHeaders().isEmpty()) {
          headers.putAll(rpcOptions.getRequestHeaders());
      }
      if (_headers != null && !_headers.isEmpty()) {
          headers.putAll(_headers);
      }
      if (_persistentHeaders != null && !_persistentHeaders.isEmpty()) {
          headers.putAll(_persistentHeaders);
      }
      return headers;
  }
}
