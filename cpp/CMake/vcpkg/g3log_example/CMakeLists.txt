cmake_minimum_required(VERSION 3.8)

project(g3log_example CXX)

find_package(g3logger CONFIG REQUIRED)

message(STATUS "G3LOG_INCLUDE_DIRS: ${G3LOG_INCLUDE_DIRS}")
message(STATUS "G3LOG_LIBRARIES: ${G3LOG_LIBRARIES}")

option(USE_MSVC_STATIC_RUNTIME "Use static version of CRT." OFF)

if (USE_MSVC_STATIC_RUNTIME)
    if (MSVC)
        foreach(flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif (MSVC)
endif (USE_MSVC_STATIC_RUNTIME)

set(BANG ON)

foreach(example_src
    main_contract.cpp
    main_fatal_choice.cpp
    main_sigsegv.cpp)
    file(DOWNLOAD
        https://raw.githubusercontent.com/KjellKod/g3log/master/example/${example_src}
        ${CMAKE_BINARY_DIR}/${example_src}
    )

    get_filename_component(example_name ${example_src} NAME_WE)

    add_executable(${example_name} ${CMAKE_BINARY_DIR}/${example_src})
    
    if (BANG)
        target_link_libraries(${example_name} PRIVATE g3logger)
        set(BANG OFF)
    else ()
        target_include_directories(${example_name} PRIVATE ${G3LOG_INCLUDE_DIRS})
        target_link_libraries(${example_name} PRIVATE ${G3LOG_LIBRARIES})
        set(BANG ON)
    endif ()
endforeach()
