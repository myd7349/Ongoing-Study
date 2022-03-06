[Amalgamation](https://github.com/EQ4/JUCEAmalgam#whats-an-amalgamation)
>## What's an amalgamation?
>
>An amalgamation is simply a collection of header and source files that have been concatenated together to form one or more very large files. In this form, they are easy to add to your existing project as source files (rather than linking as a library). They are also easier to redistribute if you are making an open source application and don't want to have any external dependencies.
>
>## Example:
>* [sqlite-amalgamation-3230100.zip](http://sqlite.org/2018/sqlite-amalgamation-3230100.zip)
>* [JuceAmalgam](https://github.com/vinniefalco/DSPFilters/tree/master/shared/JuceAmalgam)
>
>## Tools:
>* [EnTT/scripts/amalgamate.py](https://github.com/skypjack/entt/blob/master/scripts/amalgamate.py)
>* [Amalgamate](https://github.com/vinniefalco/Amalgamate)
>* [amalgamate.py](https://github.com/edlund/amalgamate) - [nlohmann/json](https://github.com/nlohmann/json/tree/develop/third_party/amalgamate) uses this tool to create a single header only library.
>* [amalgamate](https://gitlab.com/DerManu/QCustomPlot/blob/master/amalgamate)
>* [stitch.py](https://github.com/catchorg/Clara/blob/master/scripts/stitch.py) - [Clara](https://github.com/catchorg/Clara) uses this Python script to generate a single header library.
>* [cnl/src/single_header](https://github.com/johnmcfarlane/cnl/blob/develop/src/single_header/CMakeLists.txt)
>* [libnonius/nonius/tools/single_header.py](https://github.com/libnonius/nonius/blob/devel/tools/single_header.py)
>* [miniz](https://github.com/richgel999/miniz/blob/master/amalgamate.sh)
>* [open62541](https://github.com/open62541/open62541/blob/master/CMakeLists.txt#L798-L822) also uses a [Python script](https://github.com/open62541/open62541/blob/master/tools/amalgamate.py) to do amalgamation. 
>* [Outcome](https://github.com/ned14/outcome/blob/develop/CMakeLists.txt#L50) defines a CMake function named `make_single_header`.
>* [rapidjson#863](https://github.com/Tencent/rapidjson/issues/863)
>* [simdjson/amalgamation.sh](https://github.com/lemire/simdjson/blob/master/amalgamation.sh)
>* [Corrade/acme.py](https://github.com/mosra/corrade/blob/master/src/acme/acme.py)
>* [csv-parser/single_header.py](https://github.com/vincentlaucsb/csv-parser/blob/master/single_header.py)
>* [doctest/assemble_single_header.cmake](https://github.com/onqtam/doctest/blob/master/scripts/cmake/assemble_single_header.cmake)
>* [upb/tools/amalgamate.py](https://github.com/protocolbuffers/upb/blob/master/tools/amalgamate.py)
>* [mongoose amalgam.py + unamalgam.py](https://github.com/cesanta/mongoose/tree/master/tools)
>* [wepoll/tools/combine.js](https://github.com/piscisaureus/wepoll/blob/master/tools/combine.js)
>* [ned14/outcome](https://github.com/ned14/outcome/tree/develop/single-header)
>* [brigand/embed.py](https://github.com/edouarda/brigand/blob/master/script/embed.py)
>* [argtable3/tools](https://github.com/argtable/argtable3/tree/master/tools)
>* [cista/uniter](https://github.com/felixguendling/cista/blob/master/tools/uniter/uniter.cc)
>* [constexpr-sql/generator.py](https://github.com/mkitzan/constexpr-sql)
>* [libfort/amalgamate.py](https://github.com/seleznevae/libfort/blob/develop/amalgamate.py)
>* [structopt](https://github.com/p-ranav/structopt/tree/master/utils/amalgamate)
>* [single.py](https://github.com/soasis/text/blob/main/single/single.py)
>* [generate_amalgamation.py](https://github.com/wren-lang/wren/blob/main/util/generate_amalgamation.py)
>* [binary_log/utils/amalgamate](https://github.com/p-ranav/binary_log/tree/master/utils/amalgamate)
>
>## Ideas:
>* [The single-header code should be a build artifact](https://github.com/lemire/simdjson/issues/106)
>

>## References:
>[mio #23](https://github.com/mandreyel/mio/issues/23)

