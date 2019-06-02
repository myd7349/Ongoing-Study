cmake_minimum_required(VERSION 3.9)

project(protobuf-examples CXX)

find_package(protobuf CONFIG REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# http://www.cmake.org/Wiki/CMake_FAQ#How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
if(MSVC AND protobuf_MSVC_STATIC_RUNTIME)
  foreach(flag_var
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
  endforeach()
endif()

add_executable(person_cpp ${CMAKE_CURRENT_LIST_DIR}/person.cpp)

# Code generation
protobuf_generate(
    LANGUAGE cpp
    TARGET person_cpp
    PROTOS ${CMAKE_CURRENT_LIST_DIR}/person.proto
)

target_link_libraries(person_cpp PRIVATE protobuf::libprotobuf)

add_custom_command(TARGET person_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/person_with_email.json"
        $<TARGET_FILE_DIR:person_cpp>
)

add_custom_command(TARGET person_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/person_without_email.json"
        $<TARGET_FILE_DIR:person_cpp>
)


# References:
# https://github.com/protocolbuffers/protobuf/blob/master/examples/CMakeLists.txt
# https://stackoverflow.com/questions/52533396/cmake-cant-find-protobuf-protobuf-generate-cpp
# https://stackoverflow.com/questions/16736819/protobuf-generate-cpp-during-creation-of-cmake-files
