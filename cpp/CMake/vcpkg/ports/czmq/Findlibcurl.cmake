find_path(
    LIBCURL_INCLUDE_DIRS
    NAMES curl/curl.h
)

find_library(
    LIBCURL_LIBRARY_DEBUG
    NAMES libcurl-d_imp libcurl-d curl-d curl
)

find_library(
    LIBCURL_LIBRARY_RELEASE
    NAMES libcurl_imp libcurl curl
)

include(SelectLibraryConfigurations)
select_library_configurations(LIBCURL)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    LIBCURL
    REQUIRED_VARS LIBCURL_LIBRARIES LIBCURL_INCLUDE_DIRS
)

# CURL dependencies
# https://github.com/Microsoft/vcpkg/issues/4312
# https://github.com/microsoft/vcpkg/commit/ee325d14276e7bd7961e94e58293b02d6e9e92da
if (LIBCURL_FOUND)
    find_package(OpenSSL REQUIRED)
    find_package(ZLIB REQUIRED)

    list(APPEND LIBCURL_LIBRARIES
        OpenSSL::SSL
        OpenSSL::Crypto
        ZLIB::ZLIB    
    )

    if (WIN32)
        list(APPEND LIBCURL_LIBRARIES
            Crypt32
        )
    endif ()
endif ()