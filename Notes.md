# Notes and log

## 2020-06-14

* Still thinking about a way to conceptualize the function a as an object.
* The function cannot be an interface because the interface is a collection of functions.
* At this moment I thinking the the fucntion will be an interface with no menthods. A black box.
* Later we can add methods for reflection.

## 2020-06-07

* if a function is an object what is the interface?
* Will start with a function that returns something andf a context that contains parameters and the parent captures.

## 2020-05-23

* Before implementing any primitive type I need a resolver/buider for internal types:
  * Number
  * String
  * Boolean
  * Exception
  * Function

## 2020-05-22

* I decided that there will be only one type of exception with 2 string fields Code & message.
* I'm thinking about Interfaces having functions only and datataypes having data only.

## 2020-05-19

* What should We do with exceptions?
* I'm considering a single class with 2 string fields: code and message

## 2020-05-16

* Separate allocation from complex objects and primitive types.
* Consider DateTime as primitive

## 2020-05-03

* To resolve the issue with how to allocate object, we will define:
  * An object as a sequence of interfaces.
  * Interfaces are a header plus a sequence of members.
  * A member is an Identifier + a pointer to an object.
* We will try to allocate everything in a single block to reduce memory fragmentation.

## 2020-05-02

* Need to resolve how to work with managed memories and an object that is the sum of interfaces

## 2020-04-26

* Now only object has $GetInterface()

## 2020-04-25

* Only one factoly is allowed by the compiler. No parameters are allowed.

## 2020-04-24

* Design runtime object
* TODO: Define hot to manage multiple factories for an interface. 

## 2020-04-12

* For calling convention, I just use c.
* The first parameter is a pointer to the runtime.
* The runtime tracks the stack (Localvariables).
* Each function allocates it's captures, and local on the first call.
* Operations
  * Allocate Interface
  * AllocateLocalVariables
  * DeallocateLocalVariables
* Each interface structure contains the member of all the parents
* The first member is always $$GetInterface()
* Question: What should we iuse for interface ID?

## 2020-04-05

* Thinking about the function call convention
  1. Just replicate C
  2. The function sugnatures are always the same fn_call_result (RuntimeContext ctx).
  3. Do something similar to c# Task, and make everithing async by default?

* Should I define the IR code first? Should it becode PCode?
  * Well If I am using the LLVM there is no need to use pcode.

## 2020-04-04

* Update Runtime Type System Notes

## 2020-04-03

* Update Runtime Type System Notes

## 2020-04-02

* About interfaces, objects, datatypes, modules, and services.
  * An interface can inherit from multiple interfaces.
  * Only interfaces with Object can be contructed in a factory.
  * No mudules, they will only be objects.
  * Data types are a collection on serializable data values.
  * Services can only have datatypes as method parameters.  

## 2020-01-29

* Completed un managed list.
* Slow progress but this is a long term project, so no hurries.
* Still thinking the best way to implement services.
* Completed Change types respository to use lists.
* I need to rething the object hierachy.
  * How to implement IoC (Object or Module)
  * How to implement new Object (thru module?)
  * do we even have a Hierarchy,m or just alist os interfaces implemented?
