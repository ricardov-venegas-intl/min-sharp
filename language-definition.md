# Language Ideas

* Minimize Constructs
* Services are isolated, stateless and public.
  * Improves Single Responsability principle.
  * Only serilizable types are allowed in the interface
* Interfaces have inheritance, implementations don't.
  * Liskov Substitution principle
  * Variables and parameter can only be interfaces
  * Liskov Substitution principle.
  * Dependency inversion principle
* datatypes

Things to define

    * Can we skip type inferance? : Nop
    * module VS interface implementation.
      * Implemenatation only occurs in factories.
    * Import Modules.
    * Export Modules.
    * Can I modify the structure of an object after construction?

Language defined interfaces:

* IEnumerable, IEnumerator.
* IFactory.
* IModule.
* IService.
* IObject.
