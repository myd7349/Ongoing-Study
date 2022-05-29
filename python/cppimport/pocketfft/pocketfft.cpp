// cppimport
extern "C"
{
#include <pocketfft.h>
}

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>


namespace py = pybind11;


class CFFT
{
public:
    CFFT(size_t length)
        : plan_(make_cfft_plan(length))
    {
    }

    ~CFFT()
    {
        destroy_cfft_plan(plan_);
    }

    int backward(py::array_t<double> c, double fct)
    {
        py::buffer_info buf = c.request();
        return cfft_backward(plan_, static_cast<double *>(buf.ptr), fct);
    }

    int forward(py::array_t<double> c, double fct)
    {
        py::buffer_info buf = c.request();
        return cfft_forward(plan_, static_cast<double *>(buf.ptr), fct);
    }

    size_t length()
    {
        return cfft_length(plan_);
    }

    auto enter()
    {
        return py::cast(this);
    }

    void exit(py::handle type, py::handle value, py::handle traceback)
    {
        destroy_cfft_plan(plan_);
    }

private:
    cfft_plan plan_;
};


class RFFT
{
public:
    RFFT(size_t length)
        : plan_(make_rfft_plan(length))
    {
    }

    ~RFFT()
    {
        destroy_rfft_plan(plan_);
    }

    int backward(py::array_t<double> c, double fct)
    {
        py::buffer_info buf = c.request();
        return rfft_backward(plan_, static_cast<double *>(buf.ptr), fct);
    }

    int forward(py::array_t<double> c, double fct)
    {
        py::buffer_info buf = c.request();
        return rfft_forward(plan_, static_cast<double *>(buf.ptr), fct);
    }

    size_t length()
    {
        return rfft_length(plan_);
    }

    auto enter()
    {
        return py::cast(this);
    }

    void exit(py::handle type, py::handle value, py::handle traceback)
    {
        destroy_rfft_plan(plan_);
    }

private:
    rfft_plan plan_;
};


PYBIND11_MODULE(pocketfft, m)
{
    py::class_<CFFT>(m, "CFFT")
        .def(py::init<size_t>())
        .def("backward", &CFFT::backward)
        .def("forward", &CFFT::forward)
        .def("length", &CFFT::length)
        .def("__enter__", &CFFT::enter)
        .def("__exit__", &CFFT::exit);

    py::class_<RFFT>(m, "RFFT")
        .def(py::init<size_t>())
        .def("backward", &RFFT::backward)
        .def("forward", &RFFT::forward)
        .def("length", &RFFT::length)
        .def("__enter__", &RFFT::enter)
        .def("__exit__", &RFFT::exit);
}


/*
<%
cfg['dependencies'] = ['pocketfft.h']
cfg['sources'] = ['pocketfft.c']
setup_pybind11(cfg)
%>
*/


// References:
// https://github.com/numpy/numpy/blob/main/numpy/fft/_pocketfft.c
// https://github.com/pybind/python_example/blob/master/src/main.cpp
// https://pybind11.readthedocs.io/en/stable/classes.html
// https://github.com/pybind/pybind11/blob/master/docs/advanced/classes.rst
// [Sublime Text 3, convert spaces to tabs](https://stackoverflow.com/questions/22529265/sublime-text-3-convert-spaces-to-tabs)
// [pybind11—python numpy与C++数据传递](https://www.jianshu.com/p/c912a0a59af9)
// [PyBind11 destructor not invoked?](https://stackoverflow.com/questions/55452762/pybind11-destructor-not-invoked)
// [C++ destructor calling of boost::python wrapped objects](https://stackoverflow.com/questions/38228170/c-destructor-calling-of-boostpython-wrapped-objects/38238013#38238013)
// https://gist.github.com/YannickJadoul/f1fc8db711ed980cf02610277af058e4
// [pybind11: how to implement a with context manager](https://stackoverflow.com/questions/54025245/pybind11-how-to-implement-a-with-context-manager)
// https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html
// [Can't import module using pybind11](https://stackoverflow.com/questions/72175458/cant-import-module-using-pybind11)
// https://pybind11.readthedocs.io/en/stable/advanced/pycpp/object.html#casting-back-and-forth
// [pybind11: return c++ class (with an existing python binding) to python](https://stackoverflow.com/questions/54871216/pybind11-return-c-class-with-an-existing-python-binding-to-python)
// https://github.com/scipy/scipy/blob/main/scipy/fft/_pocketfft/pypocketfft.cxx
// https://github.com/scipy/scipy/blob/main/scipy/fft/_pocketfft/helper.py
