
message(">> Hello, libzmq")

find_path(LIBZMQ_INCLUDE_DIRS NAMES zmq.h)

# ZeroMQ dll/lib built with MSVC are named using the Boost convention.

if(MSVC)
    set(_zmq_versions
        "4_3_1"
        "4_3_0"
        "4_2_5"
        "4_2_4"
        "4_2_3"
        "4_2_2"
        "4_2_1"
        "4_2_0"
        "4_0_4"
        "4_0_3"
        "4_0_2"
        "4_0_1"
        "4_0_0"
        "3_2_5"
        "3_2_4"
        "3_2_3"
        "3_2_2"
        "3_2_1"
        "3_2_0"
        "3_1_0")

    set(_zmq_TOOLSET)
    set(_zmq_release_names)
    set(_zmq_debug_names)

    foreach(ver ${_zmq_versions})
        list(APPEND _zmq_release_names "libzmq${_zmq_TOOLSET}-mt-${ver}" "libzmq${_zmq_TOOLSET}-mt-s-${ver}")
    endforeach()

    foreach(ver ${_zmq_versions})
        list(APPEND _zmq_debug_names "libzmq${_zmq_TOOLSET}-mt-gd-${ver}" "libzmq${_zmq_TOOLSET}-mt-sgd-${ver}")
    endforeach()

    message(">> ${_zmq_debug_names}")
    message(">> ${_zmq_release_names}")

    find_library(ZeroMQ_LIBRARY_RELEASE
        NAMES ${_zmq_release_names} zmq libzmq
    )

    find_library(ZeroMQ_LIBRARY_DEBUG
        NAMES ${_zmq_debug_names} zmq libzmq
    )

    if(ZeroMQ_LIBRARY_RELEASE AND ZeroMQ_LIBRARY_DEBUG)
        set(LIBZMQ_LIBRARIES
            debug ${ZeroMQ_LIBRARY_DEBUG}
            optimized ${ZeroMQ_LIBRARY_RELEASE}
        )
    elseif(ZeroMQ_LIBRARY_RELEASE)
        set(LIBZMQ_LIBRARIES ${ZeroMQ_LIBRARY_RELEASE})
    elseif(ZeroMQ_LIBRARY_DEBUG)
        set(LIBZMQ_LIBRARIES ${ZeroMQ_LIBRARY_DEBUG})
    endif()

    #file(STRINGS "${LIBZMQ_INCLUDE_DIRS}/zmq.h" _version_lines
    #    REGEX "^#define.ZMQ_VERSION_(MAJOR|MINOR|PATCH).([0-9]+$)")
    #message(">> ${_version_lines}")
else ()
    find_library(LIBZMQ_LIBRARIES NAMES zmq libzmq)
endif ()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    LIBZMQ
    REQUIRED_VARS LIBZMQ_LIBRARIES LIBZMQ_INCLUDE_DIRS
)
mark_as_advanced(
    LIBZMQ_FOUND
    LIBZMQ_LIBRARIES LIBZMQ_INCLUDE_DIRS
)

# References:
# https://github.com/zeromq/czmq/issues/577
# https://stackoverflow.com/questions/31565788/cmake-find-library-with-version-number
# https://github.com/zeromq/libzmq/issues/2333
# https://bitbucket.org/ignitionrobotics/ign-transport/pull-requests/19/detec-zmq-under-windows-using-a-findzmq/diff
