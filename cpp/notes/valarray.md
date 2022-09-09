https://en.cppreference.com/w/cpp/numeric/valarray

> However, [Expression templates](https://en.wikipedia.org/wiki/Expression_templates) make the same optimization technique available for any C++ container,  and the majority of numeric libraries prefer expression templates to  valarrays for flexibility. Some C++ standard library implementations use expression templates to implement efficient operations on `std::valarray` (e.g. GNU libstdc++ and LLVM libc++). Only rarely are valarrays optimized any further, as in e.g. [Intel Integrated Performance Primitives](https://software.intel.com/en-us/node/684140).

https://eigen.tuxfamily.org/index.php?title=Main_Page

> Expression templates allow intelligently removing temporaries and enable [lazy evaluation](https://eigen.tuxfamily.org/dox/TopicLazyEvaluation.html), when that is appropriate.