# Runtime Notes

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

* T GetInterface<T>()
* Boolean ImplementsInterface<T>()

### String

A representation of a Utf value

Parents:

* Comparable<String>

### DataType

Parents:

* Object

Methods:

* T GetMemberValue<T>(member-id)
* void SetMemberValue<T>(member-id, Tvalue)
* Boolean HasMember(memberid)

Object <- ComparableObject <- String
Object <- ComparableObject <- Number
Object <- ComparableObject <- Boolean
Object <- Function

### Comparable<T>
Reprsents an entity that could be compare

Parents:

* None

Methods:

* IsBiggerThan<T>(T b)
* IsLessThan<T>(T b)
* IsEqual<T> (T b)


## Implementation notes

* Internally in runtime T is always an object