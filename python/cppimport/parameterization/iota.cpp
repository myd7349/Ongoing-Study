// 2017-01-14T19:10:03+08:00
#include <pybind11/pybind11.h>

const int End = ${end};

#define MODULE_NAME iota_${end}


#define STR_(c) #c
#define STR(c) STR_(c)


pybind11::list iota() {
    pybind11::list lst;

    for (int i = 0; i < End; ++i)
        lst.append(i);

    return lst;
}


PYBIND11_PLUGIN(MODULE_NAME) {
    pybind11::module m(STR(MODULE_NAME));

    m.def("iota", &iota);

    return m.ptr();
}

// References:
// pybind11.pdf
// Mako Documentation