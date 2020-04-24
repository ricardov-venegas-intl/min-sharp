# Notes and log

## 2020-04-12

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
   * Well If I am using the LLVM there is no need to 

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
