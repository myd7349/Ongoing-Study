cmake_minimum_required(VERSION 3.8)

project(find_python)

find_package(PythonInterp 2.7 REQUIRED)

execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "from distutils import sysconfig; print(sysconfig.get_python_lib())"
    OUTPUT_VARIABLE PYTHON_INSTDIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message("PYTHON_INSTDIR: ${PYTHON_INSTDIR}")

# References:
# https://github.com/nanopb/nanopb/blob/master/CMakeLists.txt
