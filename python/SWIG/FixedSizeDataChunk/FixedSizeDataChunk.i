// 2016-07-01T15:35+08:00
// This is an example that demonstrates the usage of `std_array.i`.
%module fixedsizedatachunk

%{
#include <array>
#include <vector>
%}

%include <std_array.i>

namespace std {
    %template(FixedSizeDataChunk) std::array<unsigned char, 1024>;
}
