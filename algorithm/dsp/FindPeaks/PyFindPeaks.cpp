<%
cfg['sources'] = ['FindPeaks.cpp']
setup_pybind11(cfg)
%>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "FindPeaks.h"


std::deque<std::size_t> FindPeaksWrapper(
    const std::vector<double> &x,
    double mph = NAN,
    std::size_t mpd = 1,
    double threshold = 0.0,
    EdgeType edge = EdgeRising,
    bool kpsh = false,
    bool valley = false)
{
    std::deque<std::size_t> peaks;
    FindPeaks(x.data(), x.size(), peaks,
        mph, mpd, threshold, edge, kpsh, valley);
    return peaks;
}


PYBIND11_MODULE(PyFindPeaks, m) {
    pybind11::enum_<EdgeType>(m, "EdgeType")
        .value("EdgeNone", EdgeType::EdgeNone)
        .value("EdgeRising", EdgeType::EdgeRising)
        .value("EdgeFalling", EdgeType::EdgeFalling)
        .value("EdgeBoth", EdgeType::EdgeBoth)
        .export_values();

    using namespace pybind11::literals;

    m.def("FindPeaks", &FindPeaksWrapper,
        "Detect peaks in data based on their amplitude and other features.",
        "x"_a,
        "mph"_a = NAN,
        "mpd"_a = 1,
        "threshold"_a = 0.0,
        "edge"_a = EdgeRising,
        "kpsh"_a = false,
        "valley"_a = false);
}
