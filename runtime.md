# Runtime Notes

## Implementation notes

* Internally in runtime, <T> is always an object, the compiler does the validations.
* All Members with names that start with the character "$" are invisible to the compiler
* The first method of all interfaces is: * T $GetInterface<T>()


## Language related Interfaces

### Runtime.AdditionOperator<T>

Parents: None

Methods:
    T Add(T rightOperand)

### Runtime.SubstractionOperator<T>

Parents: None

Methods:
    T Substract(T rightOperand)

### Runtime.MultiplicationOperator<T>

Parents: None

Methods:
    T Multiply(T rightOperand)

### Runtime.DivisionOperator<T>

Parents: None

Methods:
    T Divide(T rightOperand)

### Runtime.RemainderOperator<T>

Parents: None

Methods:
    T Remainder(T rightOperand)

## Runtime.EqualityOperator<T>

Parents: None

Methods:
    T IsEquals(T rightOperator)

## Runtime.RelationalOperator<T>

Parents: None

Methods:
    T IsGreaterThan(T rightOperator)
    T IsLowerThan(T rightOperator)

## Runtime.BooleanOperator<T>

Parents: None

Methods:
    T Or(T rightOperator)
    T And (T rightOperator)
    T Not ()

## Type Hiearchy

### Object

Any entity that cen be instantiated.

Parents:

* none

Methods:

* Boolean ImplementsInterface<T>()

### DataType

Parents:

* Object

Methods:

* T GetMemberValue<T>(member-id)
* void SetMemberValue<T>(member-id, T value)
* Boolean HasMember(memberid)

### String

A representation of a Utf value

Parents:

* Object
* Runtime.EqualityOperator<String>
* Runtime.AdditionOperator<String>
* Runtime.RelationalOperator<String>

### Number

A representation of a numeric value (bcd)

Parents:

* Object
* Runtime.EqualityOperator<Number>
* Runtime.RelationalOperator<Number>
* Runtime.AdditionOperator<Number>
* Runtime.SubstractionOperator<Number>
* Runtime.RelationalOperator<Number>
* Runtime.MultiplicationOperator<Number>
* Runtime.DivisionOperator<Number>
* Runtime.RemainderOperator<Number>

### boolean

A representation of a boolean value

Parents:

* Object
* Runtime.EqualityOperator<boolean>
* Runtime.BooleanOperator<boolean>

## Runtime Object

Provides the runtime operations needed for all functions

Parents:

* None

Members:

* $PushScope( Arrays of Local variables Address)
* $PopScope
* $Clone
* $CollectGarbage
* BuildObject<T>()
* BuildObject<T>(factoryFn)
* RegisterFactory<T>(factory)
