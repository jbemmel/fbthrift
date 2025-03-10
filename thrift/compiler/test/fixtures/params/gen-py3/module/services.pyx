#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

cimport cython
from typing import AsyncIterator
from cpython.version cimport PY_VERSION_HEX
from libc.stdint cimport (
    int8_t as cint8_t,
    int16_t as cint16_t,
    int32_t as cint32_t,
    int64_t as cint64_t,
)
from libcpp.memory cimport shared_ptr, make_shared, unique_ptr, make_unique
from libcpp.string cimport string
from libcpp cimport bool as cbool
from cpython cimport bool as pbool
from libcpp.vector cimport vector
from libcpp.set cimport set as cset
from libcpp.map cimport map as cmap
from libcpp.utility cimport move as cmove
from libcpp.pair cimport pair
from cython.operator cimport dereference as deref
from cpython.ref cimport PyObject
from thrift.py3.exceptions cimport (
    cTApplicationException,
    ApplicationError as __ApplicationError,
    cTApplicationExceptionType__UNKNOWN)
from thrift.py3.server cimport ServiceInterface, RequestContext, Cpp2RequestContext
from thrift.py3.server import RequestContext, pass_context
from folly cimport (
  cFollyPromise,
  cFollyUnit,
  c_unit,
)
from thrift.py3.common cimport (
    cThriftServiceMetadataResponse as __fbthrift_cThriftServiceMetadataResponse,
    ServiceMetadata,
    MetadataBox as __MetadataBox,
)

if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
    from thrift.py3.server cimport THRIFT_REQUEST_CONTEXT as __THRIFT_REQUEST_CONTEXT

cimport folly.futures
from folly.executor cimport get_executor
cimport folly.iobuf as _fbthrift_iobuf
import folly.iobuf as _fbthrift_iobuf
from folly.iobuf cimport move as move_iobuf
from folly.memory cimport to_shared_ptr as __to_shared_ptr

cimport module.types as _module_types
import module.types as _module_types

cimport module.services_reflection as _services_reflection

import asyncio
import functools
import sys
import traceback
import types as _py_types

from module.services_wrapper cimport cNestedContainersInterface



@cython.auto_pickle(False)
cdef class Promise_cFollyUnit:
    cdef cFollyPromise[cFollyUnit] cPromise

    @staticmethod
    cdef create(cFollyPromise[cFollyUnit] cPromise):
        cdef Promise_cFollyUnit inst = Promise_cFollyUnit.__new__(Promise_cFollyUnit)
        inst.cPromise = cmove(cPromise)
        return inst

cdef object _NestedContainers_annotations = _py_types.MappingProxyType({
})


@cython.auto_pickle(False)
cdef class NestedContainersInterface(
    ServiceInterface
):
    annotations = _NestedContainers_annotations

    def __cinit__(self):
        self._cpp_obj = cNestedContainersInterface(
            <PyObject *> self,
            get_executor()
        )

    @staticmethod
    def pass_context_mapList(fn):
        return pass_context(fn)

    async def mapList(
            self,
            foo):
        raise NotImplementedError("async def mapList is not implemented")

    @staticmethod
    def pass_context_mapSet(fn):
        return pass_context(fn)

    async def mapSet(
            self,
            foo):
        raise NotImplementedError("async def mapSet is not implemented")

    @staticmethod
    def pass_context_listMap(fn):
        return pass_context(fn)

    async def listMap(
            self,
            foo):
        raise NotImplementedError("async def listMap is not implemented")

    @staticmethod
    def pass_context_listSet(fn):
        return pass_context(fn)

    async def listSet(
            self,
            foo):
        raise NotImplementedError("async def listSet is not implemented")

    @staticmethod
    def pass_context_turtles(fn):
        return pass_context(fn)

    async def turtles(
            self,
            foo):
        raise NotImplementedError("async def turtles is not implemented")

    @classmethod
    def __get_reflection__(cls):
        return _services_reflection.get_reflection__NestedContainers(for_clients=False)

    @staticmethod
    def __get_metadata__():
        cdef __fbthrift_cThriftServiceMetadataResponse response
        ServiceMetadata[_services_reflection.cNestedContainersSvIf].gen(response)
        return __MetadataBox.box(cmove(deref(response.metadata_ref())))

    @staticmethod
    def __get_thrift_name__():
        return "module.NestedContainers"



cdef api void call_cy_NestedContainers_mapList(
    object self,
    Cpp2RequestContext* ctx,
    cFollyPromise[cFollyUnit] cPromise,
    unique_ptr[cmap[cint32_t,vector[cint32_t]]] foo
):
    cdef Promise_cFollyUnit __promise = Promise_cFollyUnit.create(cmove(cPromise))
    arg_foo = _module_types.Map__i32_List__i32.create(__to_shared_ptr(cmove(foo)))
    __context = RequestContext.create(ctx)
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __context_token = __THRIFT_REQUEST_CONTEXT.set(__context)
        __context = None
    asyncio.get_event_loop().create_task(
        NestedContainers_mapList_coro(
            self,
            __context,
            __promise,
            arg_foo
        )
    )
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __THRIFT_REQUEST_CONTEXT.reset(__context_token)

async def NestedContainers_mapList_coro(
    object self,
    object ctx,
    Promise_cFollyUnit promise,
    foo
):
    try:
        if ctx and getattr(self.mapList, "pass_context", False):
            result = await self.mapList(ctx,
                      foo)
        else:
            result = await self.mapList(
                      foo)
    except __ApplicationError as ex:
        # If the handler raised an ApplicationError convert it to a C++ one
        promise.cPromise.setException(cTApplicationException(
            ex.type.value, ex.message.encode('UTF-8')
        ))
    except Exception as ex:
        print(
            "Unexpected error in service handler mapList:",
            file=sys.stderr)
        traceback.print_exc()
        promise.cPromise.setException(cTApplicationException(
            cTApplicationExceptionType__UNKNOWN, repr(ex).encode('UTF-8')
        ))
    else:
        promise.cPromise.setValue(c_unit)

cdef api void call_cy_NestedContainers_mapSet(
    object self,
    Cpp2RequestContext* ctx,
    cFollyPromise[cFollyUnit] cPromise,
    unique_ptr[cmap[cint32_t,cset[cint32_t]]] foo
):
    cdef Promise_cFollyUnit __promise = Promise_cFollyUnit.create(cmove(cPromise))
    arg_foo = _module_types.Map__i32_Set__i32.create(__to_shared_ptr(cmove(foo)))
    __context = RequestContext.create(ctx)
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __context_token = __THRIFT_REQUEST_CONTEXT.set(__context)
        __context = None
    asyncio.get_event_loop().create_task(
        NestedContainers_mapSet_coro(
            self,
            __context,
            __promise,
            arg_foo
        )
    )
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __THRIFT_REQUEST_CONTEXT.reset(__context_token)

async def NestedContainers_mapSet_coro(
    object self,
    object ctx,
    Promise_cFollyUnit promise,
    foo
):
    try:
        if ctx and getattr(self.mapSet, "pass_context", False):
            result = await self.mapSet(ctx,
                      foo)
        else:
            result = await self.mapSet(
                      foo)
    except __ApplicationError as ex:
        # If the handler raised an ApplicationError convert it to a C++ one
        promise.cPromise.setException(cTApplicationException(
            ex.type.value, ex.message.encode('UTF-8')
        ))
    except Exception as ex:
        print(
            "Unexpected error in service handler mapSet:",
            file=sys.stderr)
        traceback.print_exc()
        promise.cPromise.setException(cTApplicationException(
            cTApplicationExceptionType__UNKNOWN, repr(ex).encode('UTF-8')
        ))
    else:
        promise.cPromise.setValue(c_unit)

cdef api void call_cy_NestedContainers_listMap(
    object self,
    Cpp2RequestContext* ctx,
    cFollyPromise[cFollyUnit] cPromise,
    unique_ptr[vector[cmap[cint32_t,cint32_t]]] foo
):
    cdef Promise_cFollyUnit __promise = Promise_cFollyUnit.create(cmove(cPromise))
    arg_foo = _module_types.List__Map__i32_i32.create(__to_shared_ptr(cmove(foo)))
    __context = RequestContext.create(ctx)
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __context_token = __THRIFT_REQUEST_CONTEXT.set(__context)
        __context = None
    asyncio.get_event_loop().create_task(
        NestedContainers_listMap_coro(
            self,
            __context,
            __promise,
            arg_foo
        )
    )
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __THRIFT_REQUEST_CONTEXT.reset(__context_token)

async def NestedContainers_listMap_coro(
    object self,
    object ctx,
    Promise_cFollyUnit promise,
    foo
):
    try:
        if ctx and getattr(self.listMap, "pass_context", False):
            result = await self.listMap(ctx,
                      foo)
        else:
            result = await self.listMap(
                      foo)
    except __ApplicationError as ex:
        # If the handler raised an ApplicationError convert it to a C++ one
        promise.cPromise.setException(cTApplicationException(
            ex.type.value, ex.message.encode('UTF-8')
        ))
    except Exception as ex:
        print(
            "Unexpected error in service handler listMap:",
            file=sys.stderr)
        traceback.print_exc()
        promise.cPromise.setException(cTApplicationException(
            cTApplicationExceptionType__UNKNOWN, repr(ex).encode('UTF-8')
        ))
    else:
        promise.cPromise.setValue(c_unit)

cdef api void call_cy_NestedContainers_listSet(
    object self,
    Cpp2RequestContext* ctx,
    cFollyPromise[cFollyUnit] cPromise,
    unique_ptr[vector[cset[cint32_t]]] foo
):
    cdef Promise_cFollyUnit __promise = Promise_cFollyUnit.create(cmove(cPromise))
    arg_foo = _module_types.List__Set__i32.create(__to_shared_ptr(cmove(foo)))
    __context = RequestContext.create(ctx)
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __context_token = __THRIFT_REQUEST_CONTEXT.set(__context)
        __context = None
    asyncio.get_event_loop().create_task(
        NestedContainers_listSet_coro(
            self,
            __context,
            __promise,
            arg_foo
        )
    )
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __THRIFT_REQUEST_CONTEXT.reset(__context_token)

async def NestedContainers_listSet_coro(
    object self,
    object ctx,
    Promise_cFollyUnit promise,
    foo
):
    try:
        if ctx and getattr(self.listSet, "pass_context", False):
            result = await self.listSet(ctx,
                      foo)
        else:
            result = await self.listSet(
                      foo)
    except __ApplicationError as ex:
        # If the handler raised an ApplicationError convert it to a C++ one
        promise.cPromise.setException(cTApplicationException(
            ex.type.value, ex.message.encode('UTF-8')
        ))
    except Exception as ex:
        print(
            "Unexpected error in service handler listSet:",
            file=sys.stderr)
        traceback.print_exc()
        promise.cPromise.setException(cTApplicationException(
            cTApplicationExceptionType__UNKNOWN, repr(ex).encode('UTF-8')
        ))
    else:
        promise.cPromise.setValue(c_unit)

cdef api void call_cy_NestedContainers_turtles(
    object self,
    Cpp2RequestContext* ctx,
    cFollyPromise[cFollyUnit] cPromise,
    unique_ptr[vector[vector[cmap[cint32_t,cmap[cint32_t,cset[cint32_t]]]]]] foo
):
    cdef Promise_cFollyUnit __promise = Promise_cFollyUnit.create(cmove(cPromise))
    arg_foo = _module_types.List__List__Map__i32_Map__i32_Set__i32.create(__to_shared_ptr(cmove(foo)))
    __context = RequestContext.create(ctx)
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __context_token = __THRIFT_REQUEST_CONTEXT.set(__context)
        __context = None
    asyncio.get_event_loop().create_task(
        NestedContainers_turtles_coro(
            self,
            __context,
            __promise,
            arg_foo
        )
    )
    if PY_VERSION_HEX >= 0x030702F0:  # 3.7.2 Final
        __THRIFT_REQUEST_CONTEXT.reset(__context_token)

async def NestedContainers_turtles_coro(
    object self,
    object ctx,
    Promise_cFollyUnit promise,
    foo
):
    try:
        if ctx and getattr(self.turtles, "pass_context", False):
            result = await self.turtles(ctx,
                      foo)
        else:
            result = await self.turtles(
                      foo)
    except __ApplicationError as ex:
        # If the handler raised an ApplicationError convert it to a C++ one
        promise.cPromise.setException(cTApplicationException(
            ex.type.value, ex.message.encode('UTF-8')
        ))
    except Exception as ex:
        print(
            "Unexpected error in service handler turtles:",
            file=sys.stderr)
        traceback.print_exc()
        promise.cPromise.setException(cTApplicationException(
            cTApplicationExceptionType__UNKNOWN, repr(ex).encode('UTF-8')
        ))
    else:
        promise.cPromise.setValue(c_unit)

