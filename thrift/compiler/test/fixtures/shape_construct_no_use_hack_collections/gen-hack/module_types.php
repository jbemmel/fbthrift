<?hh // strict
/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

/**
 * Original thrift enum:-
 * TestEnum
 */
enum TestEnum: int {
  UNKNOWN = 0;
  NEW_VALUE = 1;
}

class TestEnum_TEnumStaticMetadata implements \IThriftEnumStaticMetadata {
  public static function getEnumMetadata()[]: \tmeta_ThriftEnum {
    return tmeta_ThriftEnum::fromShape(
      shape(
        "name" => "module.TestEnum",
        "elements" => dict[
          0 => "UNKNOWN",
          1 => "NEW_VALUE",
        ],
      )
    );
  }

  public static function getAllStructuredAnnotations()[]: \TEnumAnnotations {
    return shape(
      'enum' => dict[],
      'constants' => dict[
      ],
    );
  }
}

enum TestUnionEnum: int {
  _EMPTY_ = 0;
  int_value = 1;
  str_value = 2;
  double_value = 3;
  list_of_strings = 4;
  map_of_string_to_ints = 5;
  struct_foo = 6;
}

/**
 * Original thrift struct:-
 * TestUnion
 */
class TestUnion implements \IThriftStruct, \IThriftUnion<TestUnionEnum>, \IThriftShapishStruct {
  use \ThriftUnionSerializationTrait;

  const dict<int, this::TFieldSpec> SPEC = dict[
    1 => shape(
      'var' => 'int_value',
      'union' => true,
      'type' => \TType::I32,
    ),
    2 => shape(
      'var' => 'str_value',
      'union' => true,
      'type' => \TType::STRING,
    ),
    3 => shape(
      'var' => 'double_value',
      'union' => true,
      'type' => \TType::DOUBLE,
    ),
    4 => shape(
      'var' => 'list_of_strings',
      'union' => true,
      'type' => \TType::LST,
      'etype' => \TType::STRING,
      'elem' => shape(
        'type' => \TType::STRING,
      ),
      'format' => 'array',
    ),
    5 => shape(
      'var' => 'map_of_string_to_ints',
      'union' => true,
      'type' => \TType::MAP,
      'ktype' => \TType::STRING,
      'vtype' => \TType::I32,
      'key' => shape(
        'type' => \TType::STRING,
      ),
      'val' => shape(
        'type' => \TType::I32,
      ),
      'format' => 'array',
    ),
    6 => shape(
      'var' => 'struct_foo',
      'union' => true,
      'type' => \TType::STRUCT,
      'class' => Foo::class,
    ),
  ];
  const dict<string, int> FIELDMAP = dict[
    'int_value' => 1,
    'str_value' => 2,
    'double_value' => 3,
    'list_of_strings' => 4,
    'map_of_string_to_ints' => 5,
    'struct_foo' => 6,
  ];

  const type TConstructorShape = shape(
    ?'int_value' => ?int,
    ?'str_value' => ?string,
    ?'double_value' => ?float,
    ?'list_of_strings' => ?varray<string>,
    ?'map_of_string_to_ints' => ?darray<string, int>,
    ?'struct_foo' => ?Foo,
  );

  const type TShape = shape(
    ?'int_value' => ?int,
    ?'str_value' => ?string,
    ?'double_value' => ?float,
    ?'list_of_strings' => ?varray<string>,
    ?'map_of_string_to_ints' => ?darray<string, int>,
    ?'struct_foo' => ?Foo::TShape,
  );
  const int STRUCTURAL_ID = 872350750526219001;
  /**
   * Original thrift field:-
   * 1: i32 int_value
   */
  public ?int $int_value;
  /**
   * Original thrift field:-
   * 2: string str_value
   */
  public ?string $str_value;
  /**
   * Original thrift field:-
   * 3: double double_value
   */
  public ?float $double_value;
  /**
   * Original thrift field:-
   * 4: list<string> list_of_strings
   */
  public ?varray<string> $list_of_strings;
  /**
   * Original thrift field:-
   * 5: map<string, i32> map_of_string_to_ints
   */
  public ?darray<string, int> $map_of_string_to_ints;
  /**
   * Original thrift field:-
   * 6: struct module.Foo struct_foo
   */
  public ?Foo $struct_foo;
  protected TestUnionEnum $_type = TestUnionEnum::_EMPTY_;

  public function __construct(?int $int_value = null, ?string $str_value = null, ?float $double_value = null, ?varray<string> $list_of_strings = null, ?darray<string, int> $map_of_string_to_ints = null, ?Foo $struct_foo = null  )[] {
    $this->_type = TestUnionEnum::_EMPTY_;
    if ($int_value !== null) {
      $this->int_value = $int_value;
      $this->_type = TestUnionEnum::int_value;
    }
    if ($str_value !== null) {
      $this->str_value = $str_value;
      $this->_type = TestUnionEnum::str_value;
    }
    if ($double_value !== null) {
      $this->double_value = $double_value;
      $this->_type = TestUnionEnum::double_value;
    }
    if ($list_of_strings !== null) {
      $this->list_of_strings = $list_of_strings;
      $this->_type = TestUnionEnum::list_of_strings;
    }
    if ($map_of_string_to_ints !== null) {
      $this->map_of_string_to_ints = $map_of_string_to_ints;
      $this->_type = TestUnionEnum::map_of_string_to_ints;
    }
    if ($struct_foo !== null) {
      $this->struct_foo = $struct_foo;
      $this->_type = TestUnionEnum::struct_foo;
    }
  }

  public static function withDefaultValues()[]: this {
    return new static();
  }

  public static function fromShape(self::TConstructorShape $shape)[]: this {
    return new static(
      Shapes::idx($shape, 'int_value'),
      Shapes::idx($shape, 'str_value'),
      Shapes::idx($shape, 'double_value'),
      Shapes::idx($shape, 'list_of_strings'),
      Shapes::idx($shape, 'map_of_string_to_ints'),
      Shapes::idx($shape, 'struct_foo'),
    );
  }

  public function getName()[]: string {
    return 'TestUnion';
  }

  public function getType()[]: TestUnionEnum {
    return $this->_type;
  }

  public function reset()[write_props]: void {
    switch ($this->_type) {
      case TestUnionEnum::int_value:
        $this->int_value = null;
        break;
      case TestUnionEnum::str_value:
        $this->str_value = null;
        break;
      case TestUnionEnum::double_value:
        $this->double_value = null;
        break;
      case TestUnionEnum::list_of_strings:
        $this->list_of_strings = null;
        break;
      case TestUnionEnum::map_of_string_to_ints:
        $this->map_of_string_to_ints = null;
        break;
      case TestUnionEnum::struct_foo:
        $this->struct_foo = null;
        break;
      case TestUnionEnum::_EMPTY_:
        break;
    }
    $this->_type = TestUnionEnum::_EMPTY_;
}

  public function set_int_value(int $int_value)[write_props]: this {
    $this->reset();
    $this->_type = TestUnionEnum::int_value;
    $this->int_value = $int_value;
    return $this;
  }

  public function get_int_value()[]: int {
    return $this->getx_int_value();
  }

  public function getx_int_value()[]: int {
    invariant(
      $this->_type === TestUnionEnum::int_value,
      'get_int_value called on an instance of TestUnion whose current type is %s',
      (string)$this->_type,
    );
    return $this->int_value as nonnull;
  }

  public function set_str_value(string $str_value)[write_props]: this {
    $this->reset();
    $this->_type = TestUnionEnum::str_value;
    $this->str_value = $str_value;
    return $this;
  }

  public function get_str_value()[]: string {
    return $this->getx_str_value();
  }

  public function getx_str_value()[]: string {
    invariant(
      $this->_type === TestUnionEnum::str_value,
      'get_str_value called on an instance of TestUnion whose current type is %s',
      (string)$this->_type,
    );
    return $this->str_value as nonnull;
  }

  public function set_double_value(float $double_value)[write_props]: this {
    $this->reset();
    $this->_type = TestUnionEnum::double_value;
    $this->double_value = $double_value;
    return $this;
  }

  public function get_double_value()[]: float {
    return $this->getx_double_value();
  }

  public function getx_double_value()[]: float {
    invariant(
      $this->_type === TestUnionEnum::double_value,
      'get_double_value called on an instance of TestUnion whose current type is %s',
      (string)$this->_type,
    );
    return $this->double_value as nonnull;
  }

  public function set_list_of_strings(varray<string> $list_of_strings)[write_props]: this {
    $this->reset();
    $this->_type = TestUnionEnum::list_of_strings;
    $this->list_of_strings = $list_of_strings;
    return $this;
  }

  public function get_list_of_strings()[]: varray<string> {
    return $this->getx_list_of_strings();
  }

  public function getx_list_of_strings()[]: varray<string> {
    invariant(
      $this->_type === TestUnionEnum::list_of_strings,
      'get_list_of_strings called on an instance of TestUnion whose current type is %s',
      (string)$this->_type,
    );
    return $this->list_of_strings as nonnull;
  }

  public function set_map_of_string_to_ints(darray<string, int> $map_of_string_to_ints)[write_props]: this {
    $this->reset();
    $this->_type = TestUnionEnum::map_of_string_to_ints;
    $this->map_of_string_to_ints = $map_of_string_to_ints;
    return $this;
  }

  public function get_map_of_string_to_ints()[]: darray<string, int> {
    return $this->getx_map_of_string_to_ints();
  }

  public function getx_map_of_string_to_ints()[]: darray<string, int> {
    invariant(
      $this->_type === TestUnionEnum::map_of_string_to_ints,
      'get_map_of_string_to_ints called on an instance of TestUnion whose current type is %s',
      (string)$this->_type,
    );
    return $this->map_of_string_to_ints as nonnull;
  }

  public function set_struct_foo(Foo $struct_foo)[write_props]: this {
    $this->reset();
    $this->_type = TestUnionEnum::struct_foo;
    $this->struct_foo = $struct_foo;
    return $this;
  }

  public function get_struct_foo()[]: Foo {
    return $this->getx_struct_foo();
  }

  public function getx_struct_foo()[]: Foo {
    invariant(
      $this->_type === TestUnionEnum::struct_foo,
      'get_struct_foo called on an instance of TestUnion whose current type is %s',
      (string)$this->_type,
    );
    return $this->struct_foo as nonnull;
  }

  public static function getStructMetadata()[]: \tmeta_ThriftStruct {
    return tmeta_ThriftStruct::fromShape(
      shape(
        "name" => "module.TestUnion",
        "fields" => vec[
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 1,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_I32_TYPE,
                )
              ),
              "name" => "int_value",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 2,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                )
              ),
              "name" => "str_value",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 3,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_DOUBLE_TYPE,
                )
              ),
              "name" => "double_value",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 4,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_list" => tmeta_ThriftListType::fromShape(
                    shape(
                      "valueType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "list_of_strings",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 5,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_map" => tmeta_ThriftMapType::fromShape(
                    shape(
                      "keyType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                        )
                      ),
                      "valueType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_I32_TYPE,
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "map_of_string_to_ints",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 6,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_typedef" => tmeta_ThriftTypedefType::fromShape(
                    shape(
                      "name" => "module.Foo",
                      "underlyingType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_struct" => tmeta_ThriftStructType::fromShape(
                            shape(
                              "name" => "module.Foo",
                            )
                          ),
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "struct_foo",
            )
          ),
        ],
        "is_union" => true,
      )
    );
  }

  public static function getAllStructuredAnnotations()[]: \TStructAnnotations {
    return shape(
      'struct' => dict[],
      'fields' => dict[
      ],
    );
  }

  public static function __fromShape(self::TShape $shape)[]: this {
    return new static(
      Shapes::idx($shape, 'int_value'),
      Shapes::idx($shape, 'str_value'),
      Shapes::idx($shape, 'double_value'),
      Shapes::idx($shape, 'list_of_strings'),
      Shapes::idx($shape, 'map_of_string_to_ints'),
      Shapes::idx($shape, 'struct_foo') === null ? null : (Foo::__fromShape($shape['struct_foo'])),
    );
  }

  public function __toShape()[]: self::TShape {
    return shape(
      'int_value' => $this->int_value,
      'str_value' => $this->str_value,
      'double_value' => $this->double_value,
      'list_of_strings' => $this->list_of_strings,
      'map_of_string_to_ints' => $this->map_of_string_to_ints,
      'struct_foo' => $this->struct_foo?->__toShape(),
    );
  }
}

/**
 * Original thrift struct:-
 * Foo
 */
class Foo implements \IThriftStruct, \IThriftShapishStruct {
  use \ThriftSerializationTrait;

  const dict<int, this::TFieldSpec> SPEC = dict[
    1 => shape(
      'var' => 'a',
      'type' => \TType::LST,
      'etype' => \TType::STRING,
      'elem' => shape(
        'type' => \TType::STRING,
      ),
      'format' => 'array',
    ),
    2 => shape(
      'var' => 'b',
      'type' => \TType::MAP,
      'ktype' => \TType::STRING,
      'vtype' => \TType::LST,
      'key' => shape(
        'type' => \TType::STRING,
      ),
      'val' => shape(
        'type' => \TType::LST,
        'etype' => \TType::SET,
        'elem' => shape(
          'type' => \TType::SET,
          'etype' => \TType::I32,
          'elem' => shape(
            'type' => \TType::I32,
          ),
          'format' => 'array',
        ),
        'format' => 'array',
      ),
      'format' => 'array',
    ),
    3 => shape(
      'var' => 'c',
      'type' => \TType::I64,
    ),
    4 => shape(
      'var' => 'd',
      'type' => \TType::BOOL,
    ),
    5 => shape(
      'var' => 'str_value',
      'type' => \TType::STRING,
    ),
  ];
  const dict<string, int> FIELDMAP = dict[
    'a' => 1,
    'b' => 2,
    'c' => 3,
    'd' => 4,
    'str_value' => 5,
  ];

  const type TConstructorShape = shape(
    ?'a' => ?varray<string>,
    ?'b' => ?darray<string, varray<dict<int, bool>>>,
    ?'c' => ?int,
    ?'d' => ?bool,
    ?'str_value' => ?string,
  );

  const type TShape = shape(
    'a' => varray<string>,
    ?'b' => ?darray<string, varray<dict<int, bool>>>,
    'c' => int,
    'd' => bool,
    'str_value' => string,
  );
  const int STRUCTURAL_ID = 5952652426480946901;
  /**
   * Original thrift field:-
   * 1: list<string> a
   */
  public varray<string> $a;
  /**
   * Original thrift field:-
   * 2: map<string, list<set<i32>>> b
   */
  public ?darray<string, varray<dict<int, bool>>> $b;
  /**
   * Original thrift field:-
   * 3: i64 c
   */
  public int $c;
  /**
   * Original thrift field:-
   * 4: bool d
   */
  public bool $d;
  /**
   * Original thrift field:-
   * 5: string str_value
   */
  public string $str_value;

  public function __construct(?varray<string> $a = null, ?darray<string, varray<dict<int, bool>>> $b = null, ?int $c = null, ?bool $d = null, ?string $str_value = null  )[] {
    $this->a = $a ?? varray[];
    $this->b = $b;
    $this->c = $c ?? 7;
    $this->d = $d ?? false;
    $this->str_value = $str_value ?? "hello";
  }

  public static function withDefaultValues()[]: this {
    return new static();
  }

  public static function fromShape(self::TConstructorShape $shape)[]: this {
    return new static(
      Shapes::idx($shape, 'a'),
      Shapes::idx($shape, 'b'),
      Shapes::idx($shape, 'c'),
      Shapes::idx($shape, 'd'),
      Shapes::idx($shape, 'str_value'),
    );
  }

  public function getName()[]: string {
    return 'Foo';
  }

  public static function getStructMetadata()[]: \tmeta_ThriftStruct {
    return tmeta_ThriftStruct::fromShape(
      shape(
        "name" => "module.Foo",
        "fields" => vec[
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 1,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_list" => tmeta_ThriftListType::fromShape(
                    shape(
                      "valueType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "a",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 2,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_map" => tmeta_ThriftMapType::fromShape(
                    shape(
                      "keyType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                        )
                      ),
                      "valueType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_list" => tmeta_ThriftListType::fromShape(
                            shape(
                              "valueType" => tmeta_ThriftType::fromShape(
                                shape(
                                  "t_set" => tmeta_ThriftSetType::fromShape(
                                    shape(
                                      "valueType" => tmeta_ThriftType::fromShape(
                                        shape(
                                          "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_I32_TYPE,
                                        )
                                      ),
                                    )
                                  ),
                                )
                              ),
                            )
                          ),
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "b",
              "is_optional" => true,
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 3,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_I64_TYPE,
                )
              ),
              "name" => "c",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 4,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_BOOL_TYPE,
                )
              ),
              "name" => "d",
              "is_optional" => true,
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 5,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                )
              ),
              "name" => "str_value",
            )
          ),
        ],
        "is_union" => false,
      )
    );
  }

  public static function getAllStructuredAnnotations()[]: \TStructAnnotations {
    return shape(
      'struct' => dict[],
      'fields' => dict[
      ],
    );
  }

  public static function __fromShape(self::TShape $shape)[]: this {
    return new static(
      $shape['a'],
      Shapes::idx($shape, 'b'),
      $shape['c'],
      $shape['d'],
      $shape['str_value'],
    );
  }

  public function __toShape()[]: self::TShape {
    return shape(
      'a' => $this->a,
      'b' => $this->b,
      'c' => $this->c,
      'd' => $this->d,
      'str_value' => $this->str_value,
    );
  }
}

/**
 * Original thrift struct:-
 * TestStruct
 */
class TestStruct implements \IThriftStruct, \IThriftShapishStruct {
  use \ThriftSerializationTrait;

  const dict<int, this::TFieldSpec> SPEC = dict[
    1 => shape(
      'var' => 'foo_struct',
      'type' => \TType::STRUCT,
      'class' => Foo::class,
    ),
    2 => shape(
      'var' => 'union_value',
      'type' => \TType::STRUCT,
      'class' => TestUnion::class,
    ),
    3 => shape(
      'var' => 'struct_of_self',
      'type' => \TType::STRUCT,
      'class' => TestStruct::class,
    ),
    4 => shape(
      'var' => 'list_of_struct_foo',
      'type' => \TType::LST,
      'etype' => \TType::STRUCT,
      'elem' => shape(
        'type' => \TType::STRUCT,
        'class' => Foo::class,
      ),
      'format' => 'array',
    ),
    5 => shape(
      'var' => 'map_of_string_to_struct_foo',
      'type' => \TType::MAP,
      'ktype' => \TType::STRING,
      'vtype' => \TType::STRUCT,
      'key' => shape(
        'type' => \TType::STRING,
      ),
      'val' => shape(
        'type' => \TType::STRUCT,
        'class' => Foo::class,
      ),
      'format' => 'array',
    ),
    6 => shape(
      'var' => 'list_of_struct_self',
      'type' => \TType::LST,
      'etype' => \TType::STRUCT,
      'elem' => shape(
        'type' => \TType::STRUCT,
        'class' => TestStruct::class,
      ),
      'format' => 'array',
    ),
  ];
  const dict<string, int> FIELDMAP = dict[
    'foo_struct' => 1,
    'union_value' => 2,
    'struct_of_self' => 3,
    'list_of_struct_foo' => 4,
    'map_of_string_to_struct_foo' => 5,
    'list_of_struct_self' => 6,
  ];

  const type TConstructorShape = shape(
    ?'foo_struct' => ?Foo,
    ?'union_value' => ?TestUnion,
    ?'struct_of_self' => ?TestStruct,
    ?'list_of_struct_foo' => ?varray<Foo>,
    ?'map_of_string_to_struct_foo' => ?darray<string, Foo>,
    ?'list_of_struct_self' => ?varray<TestStruct>,
  );

  const type TShape = shape(
    ?'foo_struct' => ?Foo::TShape,
    ?'union_value' => ?TestUnion::TShape,
    ?'struct_of_self' => ?TestStruct::TShape,
    'list_of_struct_foo' => varray<Foo::TShape>,
    'map_of_string_to_struct_foo' => darray<string, Foo::TShape>,
    'list_of_struct_self' => varray<TestStruct::TShape>,
  );
  const int STRUCTURAL_ID = 6681594433718475023;
  /**
   * Original thrift field:-
   * 1: struct module.Foo foo_struct
   */
  public ?Foo $foo_struct;
  /**
   * Original thrift field:-
   * 2: struct module.TestUnion union_value
   */
  public ?TestUnion $union_value;
  /**
   * Original thrift field:-
   * 3: struct module.TestStruct struct_of_self
   */
  public ?TestStruct $struct_of_self;
  /**
   * Original thrift field:-
   * 4: list<struct module.Foo> list_of_struct_foo
   */
  public varray<Foo> $list_of_struct_foo;
  /**
   * Original thrift field:-
   * 5: map<string, struct module.Foo> map_of_string_to_struct_foo
   */
  public darray<string, Foo> $map_of_string_to_struct_foo;
  /**
   * Original thrift field:-
   * 6: list<struct module.TestStruct> list_of_struct_self
   */
  public varray<TestStruct> $list_of_struct_self;

  public function __construct(?Foo $foo_struct = null, ?TestUnion $union_value = null, ?TestStruct $struct_of_self = null, ?varray<Foo> $list_of_struct_foo = null, ?darray<string, Foo> $map_of_string_to_struct_foo = null, ?varray<TestStruct> $list_of_struct_self = null  )[] {
    $this->foo_struct = $foo_struct;
    $this->union_value = $union_value;
    $this->struct_of_self = $struct_of_self;
    $this->list_of_struct_foo = $list_of_struct_foo ?? varray[];
    $this->map_of_string_to_struct_foo = $map_of_string_to_struct_foo ?? darray[];
    $this->list_of_struct_self = $list_of_struct_self ?? varray[];
  }

  public static function withDefaultValues()[]: this {
    return new static();
  }

  public static function fromShape(self::TConstructorShape $shape)[]: this {
    return new static(
      Shapes::idx($shape, 'foo_struct'),
      Shapes::idx($shape, 'union_value'),
      Shapes::idx($shape, 'struct_of_self'),
      Shapes::idx($shape, 'list_of_struct_foo'),
      Shapes::idx($shape, 'map_of_string_to_struct_foo'),
      Shapes::idx($shape, 'list_of_struct_self'),
    );
  }

  public function getName()[]: string {
    return 'TestStruct';
  }

  public static function getStructMetadata()[]: \tmeta_ThriftStruct {
    return tmeta_ThriftStruct::fromShape(
      shape(
        "name" => "module.TestStruct",
        "fields" => vec[
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 1,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_struct" => tmeta_ThriftStructType::fromShape(
                    shape(
                      "name" => "module.Foo",
                    )
                  ),
                )
              ),
              "name" => "foo_struct",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 2,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_struct" => tmeta_ThriftStructType::fromShape(
                    shape(
                      "name" => "module.TestUnion",
                    )
                  ),
                )
              ),
              "name" => "union_value",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 3,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_typedef" => tmeta_ThriftTypedefType::fromShape(
                    shape(
                      "name" => "module.TestStruct",
                      "underlyingType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_struct" => tmeta_ThriftStructType::fromShape(
                            shape(
                              "name" => "module.TestStruct",
                            )
                          ),
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "struct_of_self",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 4,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_list" => tmeta_ThriftListType::fromShape(
                    shape(
                      "valueType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_struct" => tmeta_ThriftStructType::fromShape(
                            shape(
                              "name" => "module.Foo",
                            )
                          ),
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "list_of_struct_foo",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 5,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_map" => tmeta_ThriftMapType::fromShape(
                    shape(
                      "keyType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                        )
                      ),
                      "valueType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_struct" => tmeta_ThriftStructType::fromShape(
                            shape(
                              "name" => "module.Foo",
                            )
                          ),
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "map_of_string_to_struct_foo",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 6,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_list" => tmeta_ThriftListType::fromShape(
                    shape(
                      "valueType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_typedef" => tmeta_ThriftTypedefType::fromShape(
                            shape(
                              "name" => "module.TestStruct",
                              "underlyingType" => tmeta_ThriftType::fromShape(
                                shape(
                                  "t_struct" => tmeta_ThriftStructType::fromShape(
                                    shape(
                                      "name" => "module.TestStruct",
                                    )
                                  ),
                                )
                              ),
                            )
                          ),
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "list_of_struct_self",
            )
          ),
        ],
        "is_union" => false,
      )
    );
  }

  public static function getAllStructuredAnnotations()[]: \TStructAnnotations {
    return shape(
      'struct' => dict[],
      'fields' => dict[
      ],
    );
  }

  public static function __fromShape(self::TShape $shape)[]: this {
    return new static(
      Shapes::idx($shape, 'foo_struct') === null ? null : (Foo::__fromShape($shape['foo_struct'])),
      Shapes::idx($shape, 'union_value') === null ? null : (TestUnion::__fromShape($shape['union_value'])),
      Shapes::idx($shape, 'struct_of_self') === null ? null : (TestStruct::__fromShape($shape['struct_of_self'])),
      $shape['list_of_struct_foo']
        |> Vec\map(
          $$,
          $_val0 ==> $_val0
            |> Foo::__fromShape($$),
        ) |> varray($$),
      $shape['map_of_string_to_struct_foo']
        |> Dict\map(
          $$,
          $_val1 ==> $_val1
            |> Foo::__fromShape($$),
        ) |> darray($$),
      $shape['list_of_struct_self']
        |> Vec\map(
          $$,
          $_val2 ==> $_val2
            |> TestStruct::__fromShape($$),
        ) |> varray($$),
    );
  }

  public function __toShape()[]: self::TShape {
    return shape(
      'foo_struct' => $this->foo_struct?->__toShape(),
      'union_value' => $this->union_value?->__toShape(),
      'struct_of_self' => $this->struct_of_self?->__toShape(),
      'list_of_struct_foo' => $this->list_of_struct_foo
        |> (
          Vec\map(
            $$,
            ($_val0) ==> $_val0->__toShape(),
          ) |> varray($$)
        ),
      'map_of_string_to_struct_foo' => $this->map_of_string_to_struct_foo
        |> (
          Dict\map(
            $$,
            ($_val0) ==> $_val0->__toShape(),
          ) |> darray($$)
        ),
      'list_of_struct_self' => $this->list_of_struct_self
        |> (
          Vec\map(
            $$,
            ($_val0) ==> $_val0->__toShape(),
          ) |> varray($$)
        ),
    );
  }
}

/**
 * Original thrift exception:-
 * Baz
 */
class Baz extends \TException implements \IThriftStruct {
  use \ThriftSerializationTrait;

  const dict<int, this::TFieldSpec> SPEC = dict[
    1 => shape(
      'var' => 'message',
      'type' => \TType::STRING,
    ),
    2 => shape(
      'var' => 'some_field',
      'type' => \TType::STRUCT,
      'class' => Foo::class,
    ),
    3 => shape(
      'var' => 'some_container',
      'type' => \TType::SET,
      'etype' => \TType::STRING,
      'elem' => shape(
        'type' => \TType::STRING,
      ),
      'format' => 'array',
    ),
    4 => shape(
      'var' => 'code',
      'type' => \TType::I32,
    ),
  ];
  const dict<string, int> FIELDMAP = dict[
    'message' => 1,
    'some_field' => 2,
    'some_container' => 3,
    'code' => 4,
  ];

  const type TConstructorShape = shape(
    ?'message' => ?string,
    ?'some_field' => ?Foo,
    ?'some_container' => ?dict<string, bool>,
    ?'code' => ?int,
  );

  const int STRUCTURAL_ID = 1663976252517274137;
  /**
   * Original thrift field:-
   * 1: string message
   */
  public string $message;
  /**
   * Original thrift field:-
   * 2: struct module.Foo some_field
   */
  public ?Foo $some_field;
  /**
   * Original thrift field:-
   * 3: set<string> some_container
   */
  public dict<string, bool> $some_container;
  /**
   * Original thrift field:-
   * 4: i32 code
   */
  public int $code;

  public function __construct(?string $message = null, ?Foo $some_field = null, ?dict<string, bool> $some_container = null, ?int $code = null  )[] {
    parent::__construct();
    $this->message = $message ?? '';
    $this->some_field = $some_field;
    $this->some_container = $some_container ?? dict[];
    $this->code = $code ?? 0;
  }

  public static function withDefaultValues()[]: this {
    return new static();
  }

  public static function fromShape(self::TConstructorShape $shape)[]: this {
    return new static(
      Shapes::idx($shape, 'message'),
      Shapes::idx($shape, 'some_field'),
      Shapes::idx($shape, 'some_container'),
      Shapes::idx($shape, 'code'),
    );
  }

  public function getName()[]: string {
    return 'Baz';
  }

  public static function getExceptionMetadata()[]: \tmeta_ThriftException {
    return tmeta_ThriftException::fromShape(
      shape(
        "name" => "module.Baz",
        "fields" => vec[
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 1,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                )
              ),
              "name" => "message",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 2,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_struct" => tmeta_ThriftStructType::fromShape(
                    shape(
                      "name" => "module.Foo",
                    )
                  ),
                )
              ),
              "name" => "some_field",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 3,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_set" => tmeta_ThriftSetType::fromShape(
                    shape(
                      "valueType" => tmeta_ThriftType::fromShape(
                        shape(
                          "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                        )
                      ),
                    )
                  ),
                )
              ),
              "name" => "some_container",
            )
          ),
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 4,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_I32_TYPE,
                )
              ),
              "name" => "code",
            )
          ),
        ],
      )
    );
  }

  public static function getAllStructuredAnnotations()[]: \TStructAnnotations {
    return shape(
      'struct' => dict[],
      'fields' => dict[
      ],
    );
  }

}

/**
 * Original thrift exception:-
 * OptBaz
 */
class OptBaz extends \TException implements \IThriftStruct {
  use \ThriftSerializationTrait;

  const dict<int, this::TFieldSpec> SPEC = dict[
    1 => shape(
      'var' => 'message',
      'type' => \TType::STRING,
    ),
  ];
  const dict<string, int> FIELDMAP = dict[
    'message' => 1,
  ];

  const type TConstructorShape = shape(
    ?'message' => ?string,
  );

  const int STRUCTURAL_ID = 546500496397478593;
  /**
   * Original thrift field:-
   * 1: string message
   */
  public string $message;

  public function __construct(?string $message = null  )[] {
    parent::__construct();
    $this->message = $message ?? '';
  }

  public static function withDefaultValues()[]: this {
    return new static();
  }

  public static function fromShape(self::TConstructorShape $shape)[]: this {
    return new static(
      Shapes::idx($shape, 'message'),
    );
  }

  public function getName()[]: string {
    return 'OptBaz';
  }

  public static function getExceptionMetadata()[]: \tmeta_ThriftException {
    return tmeta_ThriftException::fromShape(
      shape(
        "name" => "module.OptBaz",
        "fields" => vec[
          tmeta_ThriftField::fromShape(
            shape(
              "id" => 1,
              "type" => tmeta_ThriftType::fromShape(
                shape(
                  "t_primitive" => tmeta_ThriftPrimitiveType::THRIFT_STRING_TYPE,
                )
              ),
              "name" => "message",
              "is_optional" => true,
            )
          ),
        ],
      )
    );
  }

  public static function getAllStructuredAnnotations()[]: \TStructAnnotations {
    return shape(
      'struct' => dict[],
      'fields' => dict[
      ],
    );
  }

}

