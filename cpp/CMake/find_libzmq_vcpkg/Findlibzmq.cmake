
find_package(ZeroMQ CONFIG REQUIRED)

if (ZeroMQ_FOUND)
    message(">> ZeroMQ_LIBRARY: ${ZeroMQ_LIBRARY}")
    set(LIBZMQ_INCLUDE_DIRS ${ZeroMQ_INCLUDE_DIR})

    #if (CZMQ_BUILD_STATIC)
    if (DEFINED ZMQ_STATIC)
        message("Linked to libzmq-static")

        # When built as a static library, libzmq will set an additional
        # compiler flag `-DZMQ_STATIC` through `set_target_properties`.
        # (libzmq/CMakeLists.txt)
        #
        # Since we did not use `find_package` + `target_link_libraries`
        # here, we must define `ZMQ_STATIC` manually. Otherwise, all
        # function declarations in `zmq.h` will have a `__declspec(dllimport)`
        # specifier. 
        # https://github.com/zeromq/libzmq/issues/3318
        add_definitions(-DZMQ_STATIC=1)

        set(LIBZMQ_LIBRARIES ${ZeroMQ_LIBRARY})
    else ()
        get_target_property(_libzmq_debug_library libzmq IMPORTED_IMPLIB_DEBUG)
        get_target_property(_libzmq_release_library libzmq IMPORTED_IMPLIB_RELEASE)

        set(LIBZMQ_LIBRARIES
            debug ${_libzmq_debug_library}
            optimized ${_libzmq_release_library}
        )

        #get_target_property(_libzmq_link_libraries libzmq INTERFACE_LINK_LIBRARIES)
        #list(APPEND LIBZMQ_LIBRARIES ${_libzmq_link_libraries})
    endif ()
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
# https://github.com/zeromq/libzmq/issues/3318
# https://github.com/zeromq/czmq/issues/577
# https://stackoverflow.com/questions/31565788/cmake-find-library-with-version-number
# https://github.com/zeromq/libzmq/issues/2333
# https://bitbucket.org/ignitionrobotics/ign-transport/pull-requests/19/detec-zmq-under-windows-using-a-findzmq/diff
# https://github.com/Microsoft/vcpkg/issues/4312
# https://stackoverflow.com/questions/24231570/cmake-importing-a-static-lib-target-and-all-the-libs-it-depends-on
# https://stackoverflow.com/questions/14850736/cmake-imported-library-behaviour
# https://stackoverflow.com/questions/48545720/cmake-shared-library-how-to-get-the-lib-name-instead-of-dll-name
