#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#
cimport cython as __cython
from cpython.object cimport PyTypeObject, Py_LT, Py_LE, Py_EQ, Py_NE, Py_GT, Py_GE
from libcpp.memory cimport shared_ptr, make_shared, unique_ptr, make_unique
from libcpp.string cimport string
from libcpp cimport bool as cbool
from libcpp.iterator cimport inserter as cinserter
from cpython cimport bool as pbool
from cython.operator cimport dereference as deref, preincrement as inc, address as ptr_address
import thrift.py3.types
cimport thrift.py3.types
cimport thrift.py3.exceptions
from thrift.py3.std_libcpp cimport sv_to_str as __sv_to_str, string_view as __cstring_view
from thrift.py3.types cimport (
    cSetOp as __cSetOp,
    richcmp as __richcmp,
    set_op as __set_op,
    setcmp as __setcmp,
    list_index as __list_index,
    list_count as __list_count,
    list_slice as __list_slice,
    list_getitem as __list_getitem,
    set_iter as __set_iter,
    map_iter as __map_iter,
    map_contains as __map_contains,
    map_getitem as __map_getitem,
    reference_shared_ptr as __reference_shared_ptr,
    get_field_name_by_index as __get_field_name_by_index,
    reset_field as __reset_field,
    translate_cpp_enum_to_python,
    SetMetaClass as __SetMetaClass,
    const_pointer_cast,
    constant_shared_ptr,
    NOTSET as __NOTSET,
    EnumData as __EnumData,
    EnumFlagsData as __EnumFlagsData,
    UnionTypeEnumData as __UnionTypeEnumData,
    createEnumDataForUnionType as __createEnumDataForUnionType,
)
cimport thrift.py3.std_libcpp as std_libcpp
cimport thrift.py3.serializer as serializer
import folly.iobuf as _fbthrift_iobuf
from folly.optional cimport cOptional
from folly.memory cimport to_shared_ptr as __to_shared_ptr
from folly.range cimport Range as __cRange

import sys
from collections.abc import Sequence, Set, Mapping, Iterable
import weakref as __weakref
import builtins as _builtins

cimport module.types_reflection as _types_reflection



@__cython.auto_pickle(False)
cdef class Mixin1(thrift.py3.types.Struct):
    def __init__(Mixin1 self, **kwargs):
        self._cpp_obj = make_shared[cMixin1]()
        self._fields_setter = _fbthrift_types_fields.__Mixin1_FieldsSetter.create(self._cpp_obj.get())
        super().__init__(**kwargs)

    def __call__(Mixin1 self, **kwargs):
        if not kwargs:
            return self
        cdef Mixin1 __fbthrift_inst = Mixin1.__new__(Mixin1)
        __fbthrift_inst._cpp_obj = make_shared[cMixin1](deref(self._cpp_obj))
        __fbthrift_inst._fields_setter = _fbthrift_types_fields.__Mixin1_FieldsSetter.create(__fbthrift_inst._cpp_obj.get())
        for __fbthrift_name, _fbthrift_value in kwargs.items():
            __fbthrift_inst._fbthrift_set_field(__fbthrift_name, _fbthrift_value)
        return __fbthrift_inst

    cdef void _fbthrift_set_field(self, str name, object value) except *:
        self._fields_setter.set_field(name.encode("utf-8"), value)

    cdef object _fbthrift_isset(self):
        return thrift.py3.types._IsSet("Mixin1", {
          "field1": deref(self._cpp_obj).field1_ref().has_value(),
        })

    @staticmethod
    cdef create(shared_ptr[cMixin1] cpp_obj):
        __fbthrift_inst = <Mixin1>Mixin1.__new__(Mixin1)
        __fbthrift_inst._cpp_obj = cmove(cpp_obj)
        return __fbthrift_inst

    @property
    def field1(self):

        return (<bytes>deref(self._cpp_obj).field1_ref().value()).decode('UTF-8')


    def __hash__(Mixin1 self):
        return super().__hash__()

    def __repr__(Mixin1 self):
        return super().__repr__()

    def __str__(Mixin1 self):
        return super().__str__()


    def __copy__(Mixin1 self):
        cdef shared_ptr[cMixin1] cpp_obj = make_shared[cMixin1](
            deref(self._cpp_obj)
        )
        return Mixin1.create(cmove(cpp_obj))

    def __richcmp__(self, other, int op):
        r = self._fbthrift_cmp_sametype(other, op)
        return __richcmp[cMixin1](
            self._cpp_obj,
            (<Mixin1>other)._cpp_obj,
            op,
        ) if r is None else r

    @staticmethod
    def __get_reflection__():
        return _types_reflection.get_reflection__Mixin1()

    @staticmethod
    def __get_metadata__():
        cdef __fbthrift_cThriftMetadata meta
        StructMetadata[cMixin1].gen(meta)
        return __MetadataBox.box(cmove(meta))

    @staticmethod
    def __get_thrift_name__():
        return "module.Mixin1"

    cdef __cstring_view _fbthrift_get_field_name_by_index(self, size_t idx):
        return __get_field_name_by_index[cMixin1](idx)

    def __cinit__(self):
        self._fbthrift_struct_size = 1

    cdef _fbthrift_iobuf.IOBuf _fbthrift_serialize(Mixin1 self, __Protocol proto):
        cdef unique_ptr[_fbthrift_iobuf.cIOBuf] data
        with nogil:
            data = cmove(serializer.cserialize[cMixin1](self._cpp_obj.get(), proto))
        return _fbthrift_iobuf.from_unique_ptr(cmove(data))

    cdef cuint32_t _fbthrift_deserialize(Mixin1 self, const _fbthrift_iobuf.cIOBuf* buf, __Protocol proto) except? 0:
        cdef cuint32_t needed
        self._cpp_obj = make_shared[cMixin1]()
        with nogil:
            needed = serializer.cdeserialize[cMixin1](buf, self._cpp_obj.get(), proto)
        return needed


@__cython.auto_pickle(False)
cdef class Mixin2(thrift.py3.types.Struct):
    def __init__(Mixin2 self, **kwargs):
        self._cpp_obj = make_shared[cMixin2]()
        self._fields_setter = _fbthrift_types_fields.__Mixin2_FieldsSetter.create(self._cpp_obj.get())
        super().__init__(**kwargs)

    def __call__(Mixin2 self, **kwargs):
        if not kwargs:
            return self
        cdef Mixin2 __fbthrift_inst = Mixin2.__new__(Mixin2)
        __fbthrift_inst._cpp_obj = make_shared[cMixin2](deref(self._cpp_obj))
        __fbthrift_inst._fields_setter = _fbthrift_types_fields.__Mixin2_FieldsSetter.create(__fbthrift_inst._cpp_obj.get())
        for __fbthrift_name, _fbthrift_value in kwargs.items():
            __fbthrift_inst._fbthrift_set_field(__fbthrift_name, _fbthrift_value)
        return __fbthrift_inst

    cdef void _fbthrift_set_field(self, str name, object value) except *:
        self._fields_setter.set_field(name.encode("utf-8"), value)

    cdef object _fbthrift_isset(self):
        return thrift.py3.types._IsSet("Mixin2", {
          "m1": deref(self._cpp_obj).m1_ref().has_value(),
          "field2": deref(self._cpp_obj).field2_ref().has_value(),
        })

    @staticmethod
    cdef create(shared_ptr[cMixin2] cpp_obj):
        __fbthrift_inst = <Mixin2>Mixin2.__new__(Mixin2)
        __fbthrift_inst._cpp_obj = cmove(cpp_obj)
        return __fbthrift_inst

    @property
    def m1(self):

        if self.__fbthrift_cached_m1 is None:
            self.__fbthrift_cached_m1 = Mixin1.create(__reference_shared_ptr(deref(self._cpp_obj).m1_ref().ref(), self._cpp_obj))
        return self.__fbthrift_cached_m1

    @property
    def field2(self):
        if not deref(self._cpp_obj).field2_ref().has_value():
            return None

        return (<bytes>deref(self._cpp_obj).field2_ref().value_unchecked()).decode('UTF-8')

    @property
    def field1(self):

        return (<bytes>deref(self._cpp_obj).field1_ref().value()).decode('UTF-8')


    def __hash__(Mixin2 self):
        return super().__hash__()

    def __repr__(Mixin2 self):
        return super().__repr__()

    def __str__(Mixin2 self):
        return super().__str__()


    def __copy__(Mixin2 self):
        cdef shared_ptr[cMixin2] cpp_obj = make_shared[cMixin2](
            deref(self._cpp_obj)
        )
        return Mixin2.create(cmove(cpp_obj))

    def __richcmp__(self, other, int op):
        r = self._fbthrift_cmp_sametype(other, op)
        return __richcmp[cMixin2](
            self._cpp_obj,
            (<Mixin2>other)._cpp_obj,
            op,
        ) if r is None else r

    @staticmethod
    def __get_reflection__():
        return _types_reflection.get_reflection__Mixin2()

    @staticmethod
    def __get_metadata__():
        cdef __fbthrift_cThriftMetadata meta
        StructMetadata[cMixin2].gen(meta)
        return __MetadataBox.box(cmove(meta))

    @staticmethod
    def __get_thrift_name__():
        return "module.Mixin2"

    cdef __cstring_view _fbthrift_get_field_name_by_index(self, size_t idx):
        return __get_field_name_by_index[cMixin2](idx)

    def __cinit__(self):
        self._fbthrift_struct_size = 2

    cdef _fbthrift_iobuf.IOBuf _fbthrift_serialize(Mixin2 self, __Protocol proto):
        cdef unique_ptr[_fbthrift_iobuf.cIOBuf] data
        with nogil:
            data = cmove(serializer.cserialize[cMixin2](self._cpp_obj.get(), proto))
        return _fbthrift_iobuf.from_unique_ptr(cmove(data))

    cdef cuint32_t _fbthrift_deserialize(Mixin2 self, const _fbthrift_iobuf.cIOBuf* buf, __Protocol proto) except? 0:
        cdef cuint32_t needed
        self._cpp_obj = make_shared[cMixin2]()
        with nogil:
            needed = serializer.cdeserialize[cMixin2](buf, self._cpp_obj.get(), proto)
        return needed


@__cython.auto_pickle(False)
cdef class Mixin3Base(thrift.py3.types.Struct):
    def __init__(Mixin3Base self, **kwargs):
        self._cpp_obj = make_shared[cMixin3Base]()
        self._fields_setter = _fbthrift_types_fields.__Mixin3Base_FieldsSetter.create(self._cpp_obj.get())
        super().__init__(**kwargs)

    def __call__(Mixin3Base self, **kwargs):
        if not kwargs:
            return self
        cdef Mixin3Base __fbthrift_inst = Mixin3Base.__new__(Mixin3Base)
        __fbthrift_inst._cpp_obj = make_shared[cMixin3Base](deref(self._cpp_obj))
        __fbthrift_inst._fields_setter = _fbthrift_types_fields.__Mixin3Base_FieldsSetter.create(__fbthrift_inst._cpp_obj.get())
        for __fbthrift_name, _fbthrift_value in kwargs.items():
            __fbthrift_inst._fbthrift_set_field(__fbthrift_name, _fbthrift_value)
        return __fbthrift_inst

    cdef void _fbthrift_set_field(self, str name, object value) except *:
        self._fields_setter.set_field(name.encode("utf-8"), value)

    cdef object _fbthrift_isset(self):
        return thrift.py3.types._IsSet("Mixin3Base", {
          "field3": deref(self._cpp_obj).field3_ref().has_value(),
        })

    @staticmethod
    cdef create(shared_ptr[cMixin3Base] cpp_obj):
        __fbthrift_inst = <Mixin3Base>Mixin3Base.__new__(Mixin3Base)
        __fbthrift_inst._cpp_obj = cmove(cpp_obj)
        return __fbthrift_inst

    @property
    def field3(self):

        return (<bytes>deref(self._cpp_obj).field3_ref().value()).decode('UTF-8')


    def __hash__(Mixin3Base self):
        return super().__hash__()

    def __repr__(Mixin3Base self):
        return super().__repr__()

    def __str__(Mixin3Base self):
        return super().__str__()


    def __copy__(Mixin3Base self):
        cdef shared_ptr[cMixin3Base] cpp_obj = make_shared[cMixin3Base](
            deref(self._cpp_obj)
        )
        return Mixin3Base.create(cmove(cpp_obj))

    def __richcmp__(self, other, int op):
        r = self._fbthrift_cmp_sametype(other, op)
        return __richcmp[cMixin3Base](
            self._cpp_obj,
            (<Mixin3Base>other)._cpp_obj,
            op,
        ) if r is None else r

    @staticmethod
    def __get_reflection__():
        return _types_reflection.get_reflection__Mixin3Base()

    @staticmethod
    def __get_metadata__():
        cdef __fbthrift_cThriftMetadata meta
        StructMetadata[cMixin3Base].gen(meta)
        return __MetadataBox.box(cmove(meta))

    @staticmethod
    def __get_thrift_name__():
        return "module.Mixin3Base"

    cdef __cstring_view _fbthrift_get_field_name_by_index(self, size_t idx):
        return __get_field_name_by_index[cMixin3Base](idx)

    def __cinit__(self):
        self._fbthrift_struct_size = 1

    cdef _fbthrift_iobuf.IOBuf _fbthrift_serialize(Mixin3Base self, __Protocol proto):
        cdef unique_ptr[_fbthrift_iobuf.cIOBuf] data
        with nogil:
            data = cmove(serializer.cserialize[cMixin3Base](self._cpp_obj.get(), proto))
        return _fbthrift_iobuf.from_unique_ptr(cmove(data))

    cdef cuint32_t _fbthrift_deserialize(Mixin3Base self, const _fbthrift_iobuf.cIOBuf* buf, __Protocol proto) except? 0:
        cdef cuint32_t needed
        self._cpp_obj = make_shared[cMixin3Base]()
        with nogil:
            needed = serializer.cdeserialize[cMixin3Base](buf, self._cpp_obj.get(), proto)
        return needed


@__cython.auto_pickle(False)
cdef class Foo(thrift.py3.types.Struct):
    def __init__(Foo self, **kwargs):
        self._cpp_obj = make_shared[cFoo]()
        self._fields_setter = _fbthrift_types_fields.__Foo_FieldsSetter.create(self._cpp_obj.get())
        super().__init__(**kwargs)

    def __call__(Foo self, **kwargs):
        if not kwargs:
            return self
        cdef Foo __fbthrift_inst = Foo.__new__(Foo)
        __fbthrift_inst._cpp_obj = make_shared[cFoo](deref(self._cpp_obj))
        __fbthrift_inst._fields_setter = _fbthrift_types_fields.__Foo_FieldsSetter.create(__fbthrift_inst._cpp_obj.get())
        for __fbthrift_name, _fbthrift_value in kwargs.items():
            __fbthrift_inst._fbthrift_set_field(__fbthrift_name, _fbthrift_value)
        return __fbthrift_inst

    cdef void _fbthrift_set_field(self, str name, object value) except *:
        self._fields_setter.set_field(name.encode("utf-8"), value)

    cdef object _fbthrift_isset(self):
        return thrift.py3.types._IsSet("Foo", {
          "field4": deref(self._cpp_obj).field4_ref().has_value(),
          "m2": deref(self._cpp_obj).m2_ref().has_value(),
          "m3": deref(self._cpp_obj).m3_ref().has_value(),
        })

    @staticmethod
    cdef create(shared_ptr[cFoo] cpp_obj):
        __fbthrift_inst = <Foo>Foo.__new__(Foo)
        __fbthrift_inst._cpp_obj = cmove(cpp_obj)
        return __fbthrift_inst

    @property
    def field4(self):

        return (<bytes>deref(self._cpp_obj).field4_ref().value()).decode('UTF-8')

    @property
    def m2(self):

        if self.__fbthrift_cached_m2 is None:
            self.__fbthrift_cached_m2 = Mixin2.create(__reference_shared_ptr(deref(self._cpp_obj).m2_ref().ref(), self._cpp_obj))
        return self.__fbthrift_cached_m2

    @property
    def m3(self):

        if self.__fbthrift_cached_m3 is None:
            self.__fbthrift_cached_m3 = Mixin3Base.create(__reference_shared_ptr(deref(self._cpp_obj).m3_ref().ref(), self._cpp_obj))
        return self.__fbthrift_cached_m3

    @property
    def m1(self):

        if self.__fbthrift_cached_m1 is None:
            self.__fbthrift_cached_m1 = Mixin1.create(__reference_shared_ptr(deref(self._cpp_obj).m1_ref().ref(), self._cpp_obj))
        return self.__fbthrift_cached_m1

    @property
    def field2(self):
        if not deref(self._cpp_obj).field2_ref().has_value():
            return None

        return (<bytes>deref(self._cpp_obj).field2_ref().value_unchecked()).decode('UTF-8')

    @property
    def field1(self):

        return (<bytes>deref(self._cpp_obj).field1_ref().value()).decode('UTF-8')

    @property
    def field3(self):

        return (<bytes>deref(self._cpp_obj).field3_ref().value()).decode('UTF-8')


    def __hash__(Foo self):
        return super().__hash__()

    def __repr__(Foo self):
        return super().__repr__()

    def __str__(Foo self):
        return super().__str__()


    def __copy__(Foo self):
        cdef shared_ptr[cFoo] cpp_obj = make_shared[cFoo](
            deref(self._cpp_obj)
        )
        return Foo.create(cmove(cpp_obj))

    def __richcmp__(self, other, int op):
        r = self._fbthrift_cmp_sametype(other, op)
        return __richcmp[cFoo](
            self._cpp_obj,
            (<Foo>other)._cpp_obj,
            op,
        ) if r is None else r

    @staticmethod
    def __get_reflection__():
        return _types_reflection.get_reflection__Foo()

    @staticmethod
    def __get_metadata__():
        cdef __fbthrift_cThriftMetadata meta
        StructMetadata[cFoo].gen(meta)
        return __MetadataBox.box(cmove(meta))

    @staticmethod
    def __get_thrift_name__():
        return "module.Foo"

    cdef __cstring_view _fbthrift_get_field_name_by_index(self, size_t idx):
        return __get_field_name_by_index[cFoo](idx)

    def __cinit__(self):
        self._fbthrift_struct_size = 3

    cdef _fbthrift_iobuf.IOBuf _fbthrift_serialize(Foo self, __Protocol proto):
        cdef unique_ptr[_fbthrift_iobuf.cIOBuf] data
        with nogil:
            data = cmove(serializer.cserialize[cFoo](self._cpp_obj.get(), proto))
        return _fbthrift_iobuf.from_unique_ptr(cmove(data))

    cdef cuint32_t _fbthrift_deserialize(Foo self, const _fbthrift_iobuf.cIOBuf* buf, __Protocol proto) except? 0:
        cdef cuint32_t needed
        self._cpp_obj = make_shared[cFoo]()
        with nogil:
            needed = serializer.cdeserialize[cFoo](buf, self._cpp_obj.get(), proto)
        return needed


Mixin3 = Mixin3Base
