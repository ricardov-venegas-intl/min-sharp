# min-sharp

Personal language impired in the c# language, looking to minimize the number of concepts and constructs.

Sources of Inspiration:
The charp language: https://github.com/dotnet/csharplang
Midory: http://joeduffyblog.com/2015/11/03/blogging-about-midori/

Objectives:

* Have fun.
* Keep it as simple as possible.
* Play with LLVM :)

What not to do and expect:

* Complex language.
  * The C# Spec is is 516 page long: https://www.ecma-international.org/publications/files/ECMA-ST/ECMA-334.pdf 
  * the C== Spec is 1605 pages long :S https://www.iso.org/standard/68564.html
* Large folowup, this compiler is experimental and for fun.

Process.

* Write the compiler in min-sharp.
* Manually translate it to C.

Architectural/Features Ideas

* AOT (ahead of time) compiler.
* Nano services with no state.
* Stupidly simple GC.
  * deallocate the heap after each service call.
  * fast heap allocation
  * no static global variables
* Low cost exceptions (see http://joeduffyblog.com/2016/02/07/the-error-model/)
* Internet repositories support in lamguage (see nuger/npm)
* Support for webservices out of box
