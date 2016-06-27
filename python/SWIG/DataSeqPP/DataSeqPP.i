/* 2016-04-06T09:55+08:00 */
%module dataseqpp

%header %{
#include <new>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "../../../cpp/DLL/DataSeqPP/DataSeqPP/DataSeqPP.h"  
%}

%catches(std::bad_alloc, std::runtime_error) DataSequence::push_back;
%catches(std::invalid_argument, std::runtime_error) DataSequence::pop_back;
%catches(std::invalid_argument, std::runtime_error) DataSequence::size;
%catches(std::invalid_argument, std::out_of_range, std::runtime_error) DataSequence::at;

%ignore DataSequence::data;
%ignore DataSequence::operator[](unsigned int);
%rename(__getitem__) DataSequence::operator[](unsigned int) const;

%include "exception.i"
%include "std_string.i"
%include "std_vector.i"

// If we put this file inclusion here instead of the end of this file, then
// import dataseqpp; ds = dataseqpp.DataSequence([1.0, 2.0, 3.0])
// will not work.
// SWIG 3.0 Documentation 11.2.2 Typemap scope
// >One exception to the typemap scoping rules pertains to the %extend declaration. 
//  %extend is used to attach new declarations to a class or structure definition.
//  Because of this, all of the declarations in an %extend block are subject to the 
//  typemap rules that are in effect at the point where the class itself is defined.
//%include "../../../cpp/DLL/DataSeqPP/DataSeqPP/DataSeqPP.h"

namespace std {
    %template(DoubleVector) vector<double>;
}

// You may:
// import dataseqpp
// ds = dataseqpp.DataSequence([1, 2, 3])
// for i in ds: print(i)
%exception DataSequence::operator[](unsigned int) const {
    try {
        $action
    } catch (std::exception &e) {
        SWIG_exception(SWIG_IndexError, e.what());
    }
}

%extend DataSequence {
    // In the target Python module, you may:
    // import dataseqpp
    // ds = dataseqpp.DataSequence([1, 2, 3])
    DataSequence(const std::vector<double> &elems) {
        DataSequence *ds = new DataSequence(elems.size());
        for (std::vector<double>::size_type i = 0; i < elems.size(); ++i)
            ds->at(i) = elems[i];
        return ds;
    }

    std::string __repr__() const {
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

    void __setitem__(unsigned int i, double v) {
        $self->operator[](i) = v;
    }

    unsigned __len__() const {
        return $self->size();
    }

    // You may:
    // ds.push_back([42.0, 3.14])
    void push_back(const std::vector<double> &elems) {
        for (std::vector<double>::size_type i = 0; i < elems.size(); ++i)
            $self->push_back(elems[i]);
    }
};

%include "../../../cpp/DLL/DataSeqPP/DataSeqPP/DataSeqPP.h"

// References:
// SWIGDocumentation.pdf
//  -- 9.4.2 std::vector
//  -- 12.1.7 Using The SWIG exception library
