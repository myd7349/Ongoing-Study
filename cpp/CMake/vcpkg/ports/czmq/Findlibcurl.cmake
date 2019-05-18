# https://github.com/Microsoft/vcpkg/issues/4312
# https://github.com/microsoft/vcpkg/commit/ee325d14276e7bd7961e94e58293b02d6e9e92da
find_package(CURL QUIET)

if (CURL_FOUND)
    set(LIBCURL_FOUND ${CURL_FOUND})
    set(LIBCURL_INCLUDE_DIRS ${CURL_INCLUDE_DIRS})

    find_package(OpenSSL REQUIRED)
    find_package(ZLIB REQUIRED)

    set(LIBCURL_LIBRARIES
        ${CURL_LIBRARIES}
        # CURL dependencies
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
