cmake_minimum_required(VERSION 3.9)

project(vcpkg_check_features_test C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(${CMAKE_CURRENT_LIST_DIR}/vcpkg_check_features.cmake)

set(ALL_FEATURES
    curl
    drafts
    httpd
    lz4
    tools
    uuid
)

set(FEATURES
    drafts
    tools
)

vcpkg_check_feature(curl CZMQ_WITH_LIBCURL)
message(STATUS "CZMQ_WITH_LIBCURL: ${CZMQ_WITH_LIBCURL}")

vcpkg_check_feature(tools BUILD_TOOLS)
message(STATUS "BUILD_TOOLS: ${BUILD_TOOLS}")

#vcpkg_check_feature("" CZMQ_WITH_EMPTY)
#message(STATUS "CZMQ_WITH_EMPTY: ${CZMQ_WITH_EMPTY}")

#vcpkg_check_feature(xxx CZMQ_WITH_XXX)
#message(STATUS "CZMQ_WITH_XXX: ${CZMQ_WITH_XXX}")

vcpkg_check_features(
    curl CZMQ_WITH_LIBCURL
    drafts BUILD_DRAFTS_API
    tools BUILD_TOOLS
)
message(STATUS "CZMQ_WITH_LIBCURL: ${CZMQ_WITH_LIBCURL}")
message(STATUS "BUILD_DRAFTS_API: ${BUILD_DRAFTS_API}")
message(STATUS "BUILD_TOOLS: ${BUILD_TOOLS}")
message(STATUS "FEATURE_OPTIONS: ${FEATURE_OPTIONS}")

list(APPEND FEATURES curl)
vcpkg_check_features(curl CZMQ_WITH_LIBCURL)
message(STATUS "FEATURE_OPTIONS: ${FEATURE_OPTIONS}")

vcpkg_check_features()
message(STATUS "FEATURE_OPTIONS: ${FEATURE_OPTIONS}")
