/*cppimport
<%
setup_pybind11(cfg)
cfg['dependencies'] = ['CUSUMChangeDetector.h']
%>
*/

#include <pybind11/pybind11.h>

#include "CUSUMChangeDetector.h"


PYBIND11_MODULE(pycumsum, m) {
    pybind11::class_<CUSUMChangeDetector>(m, "CUSUMChangeDetector")
        .def(pybind11::init<double, double, int>())
        .def("update", &CUSUMChangeDetector::Update)
        .def("is_changed", &CUSUMChangeDetector::IsChange)
        .def("is_ready", &CUSUMChangeDetector::IsReady)
        .def("reset", &CUSUMChangeDetector::Reset);
}
