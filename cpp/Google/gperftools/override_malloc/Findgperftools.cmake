# https://github.com/ceph/ceph/blob/master/cmake/modules/Findgperftools.cmake
# Try to find gperftools
# Once done, this will define
#
# gperftools_FOUND - system has Profiler
# GPERFTOOLS_INCLUDE_DIR - the Profiler include directories
# Tcmalloc_INCLUDE_DIR - where to find Tcmalloc.h
# GPERFTOOLS_TCMALLOC_LIBRARY - link it to use tcmalloc
# GPERFTOOLS_TCMALLOC_MINIMAL_LIBRARY - link it to use tcmalloc_minimal
# GPERFTOOLS_PROFILER_LIBRARY - link it to use Profiler
# TCMALLOC_VERSION_STRING
# TCMALLOC_VERSION_MAJOR
# TCMALLOC_VERSION_MINOR
# TCMALLOC_VERSION_PATCH

find_path(GPERFTOOLS_INCLUDE_DIR gperftools/profiler.h
  HINTS $ENV{GPERF_ROOT}/include)
find_path(Tcmalloc_INCLUDE_DIR gperftools/tcmalloc.h
  HINTS $ENV{GPERF_ROOT}/include)

if(Tcmalloc_INCLUDE_DIR AND EXISTS "${Tcmalloc_INCLUDE_DIR}/gperftools/tcmalloc.h")
  foreach(ver "MAJOR" "MINOR" "PATCH")
    file(STRINGS "${Tcmalloc_INCLUDE_DIR}/gperftools/tcmalloc.h" TC_VER_${ver}_LINE
      REGEX "^#define[ \t]+TC_VERSION_${ver}[ \t]+[^ \t]+$")
    string(REGEX REPLACE "^#define[ \t]+TC_VERSION_${ver}[ \t]+(\".)?([0-9]*)\"?$"
      "\\2" TCMALLOC_VERSION_${ver} "${TC_VER_${ver}_LINE}")
    unset(TC_VER_${ver}_LINE)
  endforeach()
  set(TCMALLOC_VERSION_STRING "${TCMALLOC_VERSION_MAJOR}.${TCMALLOC_VERSION_MINOR}")
  if(NOT TCMALLOC_VERSION_PATCH STREQUAL "")
    set(TCMALLOC_VERSION_STRING "${TCMALLOC_VERSION_STRING}.${TCMALLOC_VERSION_PATCH}")
  endif()
endif()

get_filename_component(_prefix_path ${GPERFTOOLS_INCLUDE_DIR} PATH)

include(SelectLibraryConfigurations)

foreach(component tcmalloc tcmalloc_minimal profiler)
  string(TOUPPER ${component} COMPONENT)
  find_library(
    GPERFTOOLS_${COMPONENT}_LIBRARY_DEBUG
    NAMES lib${component}_debug lib${component} ${component}
    PATHES ${_prefix_path}/debug/lib
    HINTS $ENV{GPERF_ROOT}/lib
    NO_DEFAULT_PATH)
  find_library(
    GPERFTOOLS_${COMPONENT}_LIBRARY_RELEASE
    NAMES lib${component} ${component}
    PATHES ${_prefix_path}/lib
    HINTS $ENV{GPERF_ROOT}/lib
    NO_DEFAULT_PATH)
  select_library_configurations(GPERFTOOLS_${COMPONENT})
  message(STATUS "GPERFTOOLS_${COMPONENT}_LIBRARY_DEBUG: ${GPERFTOOLS_${COMPONENT}_LIBRARY_DEBUG}")
  message(STATUS "GPERFTOOLS_${COMPONENT}_LIBRARY_RELEASE: ${GPERFTOOLS_${COMPONENT}_LIBRARY_RELEASE}")
  message(STATUS "GPERFTOOLS_${COMPONENT}_LIBRARY: ${GPERFTOOLS_${COMPONENT}_LIBRARY}")
  message(STATUS "GPERFTOOLS_${COMPONENT}_LIBRARIES: ${GPERFTOOLS_${COMPONENT}_LIBRARIES}")
  if(GPERFTOOLS_${COMPONENT}_LIBRARIES)
    list(APPEND GPERFTOOLS_LIBRARIES ${GPERFTOOLS_${COMPONENT}_LIBRARIES})
  elseif(GPERFTOOLS_${COMPONENT}_LIBRARY)
    list(APPEND GPERFTOOLS_LIBRARIES ${GPERFTOOLS_${COMPONENT}_LIBRARY})
  endif()
endforeach()

set(_gperftools_FIND_REQUIRED_VARS "GPERFTOOLS_INCLUDE_DIR")
if(gperftools_FIND_COMPONENTS)
  foreach(component ${gperftools_FIND_COMPONENTS})
    string(TOUPPER ${component} COMPONENT)
    list(APPEND _gperftools_FIND_REQUIRED_VARS "GPERFTOOLS_${COMPONENT}_LIBRARY")
  endforeach()
else()
  list(APPEND _gperftools_FIND_REQUIRED_VARS "GPERFTOOLS_LIBRARIES")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gperftools
  FOUND_VAR gperftools_FOUND
  REQUIRED_VARS ${_gperftools_FIND_REQUIRED_VARS}
  VERSION_VAR TCMALLOC_VERSION_STRING)

mark_as_advanced(${GPERFTOOLS_LIBRARIES} GPERFTOOLS_INCLUDE_DIR)

if(gperftools_FOUND)
  foreach(component tcmalloc tcmalloc_minimal profiler)
    if(NOT (TARGET gperftools::${component}))
      string(TOUPPER ${component} COMPONENT)
      add_library(gperftools::${component} UNKNOWN IMPORTED)
      set_target_properties(gperftools::${component} PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${GPERFTOOLS_INCLUDE_DIR}"
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${GPERFTOOLS_${COMPONENT}_LIBRARY}")
    endif()
  endforeach()
  foreach(component tcmalloc tcmalloc_minimal)
    if(NOT (TARGET gperftools::${component}))
      set_target_properties(gperftools::${component} PROPERTIES
        INTERFACE_COMPILE_OPTIONS "-fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free")
    endif()
  endforeach()
endif()

message(STATUS "gperftools_FOUND: ${gperftools_FOUND}")
message(STATUS "GPERFTOOLS_INCLUDE_DIR: ${GPERFTOOLS_INCLUDE_DIR}")
message(STATUS "GPERFTOOLS_LIBRARIES: ${GPERFTOOLS_LIBRARIES}")
