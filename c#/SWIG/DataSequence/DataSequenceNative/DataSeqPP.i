/* 2016-04-06T09:55+08:00 */
%module DataSequenceNative

%{
#include <new>
#include <sstream>
#include <stdexcept>

#include "../../../../cpp/DLL/DataSeqPP/DataSeqPP/DataSeqPP.h"  
%}

%catches(std::bad_alloc, std::runtime_error) DataSequence::push_back;
%catches(std::invalid_argument, std::runtime_error) DataSequence::pop_back;
%catches(std::invalid_argument, std::runtime_error) DataSequence::size;
%catches(std::invalid_argument, std::out_of_range, std::runtime_error) DataSequence::at;
%ignore DataSequence::data;
%rename("%(camelcase)s", %$isfunction) "";

%csmethodmodifiers DataSequence::ToString "public override";

%include "std_string.i"
%include "../../../../cpp/DLL/DataSeqPP/DataSeqPP/DataSeqPP.h"

%extend DataSequence {
    std::string ToString() const {
        unsigned int size = 0;
        try {
            size = $self->size();
        } catch (...) {
            return "<invalid data sequence>";
        }

        if (size == 0)
            return "<empty>";

        std::ostringstream oss;
        oss << "[" << $self->operator[](0);
        for (unsigned i = 1; i < size; ++i)
            oss << ", " << $self->operator[](i);
        oss << "]";

        return oss.str();
    }
};