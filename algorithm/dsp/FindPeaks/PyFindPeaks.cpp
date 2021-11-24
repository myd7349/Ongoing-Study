<%
cfg['sources'] = ['FindPeaks.cpp']
setup_pybind11(cfg)
%>
#include "PyFindPeaksImpl.cpp"
