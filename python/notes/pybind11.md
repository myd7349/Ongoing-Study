Binding Generators
====

* [binder](https://github.com/RosettaCommons/binder)

* [cppimport](https://github.com/tbenthompson/cppimport)
  
  BTW, Cython also provides a similar tool: [pyximport](https://github.com/cython/cython/tree/master/pyximport).

Projects using `pybind11`
====

* [OpenPano](https://github.com/ppwwyyxx/OpenPano/blob/master/src/python/pybind.cc)
* [hnswlib](https://github.com/nmslib/hnswlib)
* [nmslib](https://github.com/nmslib/nmslib)
* [xeus-python](https://github.com/QuantStack/xeus-python)
* [dlib](https://github.com/davisking/dlib/blob/master/setup.py)
* [bimpy](https://github.com/podgorskiy/bimpy)
* [pysimdjson](https://github.com/TkTech/pysimdjson)
* [pymetis](https://github.com/inducer/pymetis)
* [flashlight](https://github.com/flashlight/flashlight/tree/master/bindings/python)
* [pyworkflow](https://github.com/sogou/pyworkflow)
* [LaunchyQt](https://github.com/samsonwang/LaunchyQt)
* [OpenXLSX](https://github.com/troldal/OpenXLSX/tree/master/Python)
* [optima](https://github.com/reaktoro/optima/blob/master/python/bindings/CMakeLists.txt)
* [pymeshlab](https://github.com/cnr-isti-vclab/PyMeshLab/tree/master/src/pymeshlab)
* [pykokkos-base](https://github.com/kokkos/pykokkos-base)
  - [pykokkos](https://github.com/kokkos/pykokkos)
* [OpenJij](https://github.com/OpenJij/OpenJij/tree/master/openjij)
* [pytomlpp](https://github.com/bobfang1992/pytomlpp)
* [PyFastPFor](https://github.com/searchivarius/PyFastPFor)
* [qdb-api-python](https://github.com/bureau14/qdb-api-python)
* [OpenCC](https://github.com/BYVoid/OpenCC/blob/master/src/py_opencc.cpp)
* [TensorRT](https://github.com/NVIDIA/TensorRT/tree/main/python)
* [traji](https://github.com/cmpute/traji)
* [pedalboard](https://github.com/spotify/pedalboard)
* [NumPyEigen](https://github.com/fwilliams/numpyeigen)
  - [libigl-python-bindings](https://github.com/libigl/libigl-python-bindings)
* [tiledarray](https://github.com/ValeevGroup/tiledarray)
* [gemmi](https://github.com/project-gemmi/gemmi)
* [gnuradio](https://github.com/gnuradio/gnuradio)
* [pygalmesh](https://github.com/meshpro/pygalmesh)
* [LIEF](https://github.com/lief-project/LIEF)
* [ducc](https://github.com/mreineck/ducc)
* [SciPy](https://github.com/scipy/scipy/blob/main/scipy/spatial/src/distance_pybind.cpp)
  * [scipy.fft](https://github.com/scipy/scipy/blob/main/scipy/fft/_pocketfft/pypocketfft.cxx)
* [skia-python](https://github.com/kyamagu/skia-python)
* [imprint](https://github.com/Confirm-Solutions/imprint)
* [envpool](https://github.com/sail-sg/envpool)
* [openPMD-api](https://github.com/openPMD/openPMD-api)
* [warp-ctc](https://github.com/SeanNaren/warp-ctc)
* [pybind11_protobuf](https://github.com/pybind/pybind11_protobuf)

# Notes

1. https://pybind11.readthedocs.io/en/stable/compiling.html
   
   > ```python
   > from glob import glob
   > from setuptools import setup
   > from pybind11.setup_helpers import Pybind11Extension
   > 
   > ext_modules = [
   >  Pybind11Extension(
   >      "python_example",
   >      sorted(glob("src/*.cpp")),  # Sort source files for reproducibility
   >  ),
   > ]
   > 
   > setup(..., ext_modules=ext_modules)
   > ```

2. pybind11_add_module
   
   > ```cmake
   > # Ongoing-Study/algorithm/dsp/FindPeaks/CMakeLists.txt
   > if(BUILD_PYFINDPEAKS)
   >  include(FetchContent)
   > 
   >  FetchContent_Declare(
   >      pybind11
   >      GIT_REPOSITORY https://github.com/pybind/pybind11
   >      GIT_TAG        v2.8.1
   >  )
   > 
   >  FetchContent_GetProperties(pybind11)
   >  if(NOT pybind11_POPULATED)
   >      FetchContent_Populate(pybind11)
   >      add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
   >  endif()
   > 
   >  pybind11_add_module(PyFindPeaks PyFindPeaksImpl.cpp)
   >  target_link_libraries(PyFindPeaks PRIVATE FindPeaks)
   > endif()
   > ```
   >
   > 
