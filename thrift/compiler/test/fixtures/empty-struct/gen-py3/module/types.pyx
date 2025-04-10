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



cdef __UnionTypeEnumData __Nada_union_type_enum_data  = __UnionTypeEnumData.create(
    __createEnumDataForUnionType[cNada](),
    __NadaType,
)


@__cython.internal
@__cython.auto_pickle(False)
cdef class __Nada_Union_TypeMeta(thrift.py3.types.EnumMeta):
    def _fbthrift_get_by_value(cls, int value):
        return __Nada_union_type_enum_data.get_by_value(value)

    def _fbthrift_get_all_names(cls):
        return __Nada_union_type_enum_data.get_all_names()

    def __len__(cls):
        return __Nada_union_type_enum_data.size()

    def __getattribute__(cls, str name not None):
        if name.startswith("__") or name.startswith("_fbthrift_") or name == "mro":
            return super().__getattribute__(name)
        return __Nada_union_type_enum_data.get_by_name(name)


@__cython.final
@__cython.auto_pickle(False)
cdef class __NadaType(thrift.py3.types.CompiledEnum):
    cdef get_by_name(self, str name):
        return __Nada_union_type_enum_data.get_by_name(name)


__SetMetaClass(<PyTypeObject*> __NadaType, <PyTypeObject*> __Nada_Union_TypeMeta)


@__cython.auto_pickle(False)
cdef class Empty(thrift.py3.types.Struct):
    def __init__(Empty self, **kwargs):
        self._cpp_obj = make_shared[cEmpty]()
        self._fields_setter = _fbthrift_types_fields.__Empty_FieldsSetter.create(self._cpp_obj.get())
        super().__init__(**kwargs)

    def __call__(Empty self, **kwargs):
        return self

    cdef void _fbthrift_set_field(self, str name, object value) except *:
        self._fields_setter.set_field(name.encode("utf-8"), value)

    cdef object _fbthrift_isset(self):
        return thrift.py3.types._IsSet("Empty", {
        })

    @staticmethod
    cdef create(shared_ptr[cEmpty] cpp_obj):
        __fbthrift_inst = <Empty>Empty.__new__(Empty)
        __fbthrift_inst._cpp_obj = cmove(cpp_obj)
        return __fbthrift_inst


    def __hash__(Empty self):
        return super().__hash__()

    def __repr__(Empty self):
        return super().__repr__()

    def __str__(Empty self):
        return super().__str__()


    def __copy__(Empty self):
        cdef shared_ptr[cEmpty] cpp_obj = make_shared[cEmpty](
            deref(self._cpp_obj)
        )
        return Empty.create(cmove(cpp_obj))

    def __richcmp__(self, other, int op):
        r = self._fbthrift_cmp_sametype(other, op)
        return __richcmp[cEmpty](
            self._cpp_obj,
            (<Empty>other)._cpp_obj,
            op,
        ) if r is None else r

    @staticmethod
    def __get_reflection__():
        return _types_reflection.get_reflection__Empty()

    @staticmethod
    def __get_metadata__():
        cdef __fbthrift_cThriftMetadata meta
        StructMetadata[cEmpty].gen(meta)
        return __MetadataBox.box(cmove(meta))

    @staticmethod
    def __get_thrift_name__():
        return "module.Empty"

    cdef __cstring_view _fbthrift_get_field_name_by_index(self, size_t idx):
        return __get_field_name_by_index[cEmpty](idx)

    def __cinit__(self):
        self._fbthrift_struct_size = 0

    cdef _fbthrift_iobuf.IOBuf _fbthrift_serialize(Empty self, __Protocol proto):
        cdef unique_ptr[_fbthrift_iobuf.cIOBuf] data
        with nogil:
            data = cmove(serializer.cserialize[cEmpty](self._cpp_obj.get(), proto))
        return _fbthrift_iobuf.from_unique_ptr(cmove(data))

    cdef cuint32_t _fbthrift_deserialize(Empty self, const _fbthrift_iobuf.cIOBuf* buf, __Protocol proto) except? 0:
        cdef cuint32_t needed
        self._cpp_obj = make_shared[cEmpty]()
        with nogil:
            needed = serializer.cdeserialize[cEmpty](buf, self._cpp_obj.get(), proto)
        return needed




@__cython.auto_pickle(False)
cdef class Nada(thrift.py3.types.Union):
    Type = __NadaType

    def __init__(
        self, *
    ):
        self._cpp_obj = __to_shared_ptr(cmove(Nada._make_instance(
          NULL,
        )))
        self._load_cache()

    @staticmethod
    def fromValue(value):
        if value is None:
            return Nada()
        raise ValueError(f"Unable to derive correct union field for value: {value}")

    @staticmethod
    cdef unique_ptr[cNada] _make_instance(
        cNada* base_instance
    ) except *:
        cdef unique_ptr[cNada] c_inst = make_unique[cNada]()
        cdef bint any_set = False
        # in C++ you don't have to call move(), but this doesn't translate
        # into a C++ return statement, so you do here
        return cmove(c_inst)

    @staticmethod
    cdef create(shared_ptr[cNada] cpp_obj):
        __fbthrift_inst = <Nada>Nada.__new__(Nada)
        __fbthrift_inst._cpp_obj = cmove(cpp_obj)
        __fbthrift_inst._load_cache()
        return __fbthrift_inst


    def __hash__(Nada self):
        return  super().__hash__()

    cdef _load_cache(Nada self):
        self.type = Nada.Type(<int>(deref(self._cpp_obj).getType()))
        cdef int type = self.type.value
        if type == 0:    # Empty
            self.value = None

    def __copy__(Nada self):
        cdef shared_ptr[cNada] cpp_obj = make_shared[cNada](
            deref(self._cpp_obj)
        )
        return Nada.create(cmove(cpp_obj))

    def __richcmp__(self, other, int op):
        r = self._fbthrift_cmp_sametype(other, op)
        return __richcmp[cNada](
            self._cpp_obj,
            (<Nada>other)._cpp_obj,
            op,
        ) if r is None else r

    @staticmethod
    def __get_reflection__():
        return _types_reflection.get_reflection__Nada()

    @staticmethod
    def __get_metadata__():
        cdef __fbthrift_cThriftMetadata meta
        StructMetadata[cNada].gen(meta)
        return __MetadataBox.box(cmove(meta))

    @staticmethod
    def __get_thrift_name__():
        return "module.Nada"

    cdef __cstring_view _fbthrift_get_field_name_by_index(self, size_t idx):
        return __get_field_name_by_index[cNada](idx)

    def __cinit__(self):
        self._fbthrift_struct_size = 0

    cdef _fbthrift_iobuf.IOBuf _fbthrift_serialize(Nada self, __Protocol proto):
        cdef unique_ptr[_fbthrift_iobuf.cIOBuf] data
        with nogil:
            data = cmove(serializer.cserialize[cNada](self._cpp_obj.get(), proto))
        return _fbthrift_iobuf.from_unique_ptr(cmove(data))

    cdef cuint32_t _fbthrift_deserialize(Nada self, const _fbthrift_iobuf.cIOBuf* buf, __Protocol proto) except? 0:
        cdef cuint32_t needed
        self._cpp_obj = make_shared[cNada]()
        with nogil:
            needed = serializer.cdeserialize[cNada](buf, self._cpp_obj.get(), proto)
        # force a cache reload since the underlying data's changed
        self._load_cache()
        return needed


