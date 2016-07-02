// 2016-07-02T17:55+08:00
%module CPP11StdArrayNative

%include "std_array.i"
%include <std_wstring.i>

namespace std {
    %template(Bytes1024) array<unsigned char, 1024>;
	%template(EmptyBuffer) array<unsigned char, 0>;
	%template(GoF) array<wstring, 4>;
}