cmake_minimum_required(VERSION 3.9)

project(libsodium_test)

include(CTest)

find_package(unofficial-sodium CONFIG REQUIRED)

message(STATUS "sodium_FOUND: ${sodium_FOUND}")
message(STATUS "sodium_VERSION: ${sodium_VERSION}")
message(STATUS "sodium_INCLUDE_DIR: ${sodium_INCLUDE_DIR}")
message(STATUS "sodium_LIBRARY_DEBUG: ${sodium_LIBRARY_DEBUG}")
message(STATUS "sodium_LIBRARY_RELEASE: ${sodium_LIBRARY_RELEASE}")
message(STATUS "sodium_LIBRARIES: ${sodium_LIBRARIES}")
message(STATUS "sodium_DLL_DEBUG: ${sodium_DLL_DEBUG}")
message(STATUS "sodium_DLL_RELEASE: ${sodium_DLL_RELEASE}")

if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/test")
    message(WARNING "Downloading all the test source files from GitHub one by one is too slow. Please consider clone the libsodium repository first, and then copy the \"test\" subdirectory to this directory.")
endif ()

if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/test/quirks/quirks.h")
    message(STATUS "Downloading quirks.h ...")

    file(DOWNLOAD
        "https://raw.githubusercontent.com/jedisct1/libsodium/master/test/quirks/quirks.h"
        "${CMAKE_CURRENT_LIST_DIR}/test/quirks/quirks.h")
endif ()

if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/test/default/cmptest.h")
    message(STATUS "Downloading cmptest.h ...")

    file(DOWNLOAD
        "https://raw.githubusercontent.com/jedisct1/libsodium/master/test/default/cmptest.h"
        "${CMAKE_CURRENT_LIST_DIR}/test/default/cmptest.h")
endif ()

set(test_sources
    aead_aes256gcm.c
    aead_aes256gcm2.c
    aead_chacha20poly1305.c
    aead_chacha20poly13052.c
    aead_xchacha20poly1305.c
    auth.c
    auth2.c
    auth3.c
    auth5.c
    auth6.c
    auth7.c
    box.c
    box2.c
    box7.c
    box8.c
    box_easy.c
    box_easy2.c
    box_seal.c
    box_seed.c
    chacha20.c
    codecs.c
    core1.c
    core2.c
    core3.c
    core4.c
    core5.c
    core6.c
    core_ed25519.c
    ed25519_convert.c
    generichash.c
    generichash2.c
    generichash3.c
    hash.c
    hash3.c
    kdf.c
    keygen.c
    kx.c
    metamorphic.c
    misuse.c
    onetimeauth.c
    onetimeauth2.c
    onetimeauth7.c
    pwhash_argon2i.c
    pwhash_argon2id.c
    pwhash_scrypt.c
    pwhash_scrypt_ll.c
    randombytes.c
    scalarmult.c
    scalarmult2.c
    scalarmult5.c
    scalarmult6.c
    scalarmult7.c
    scalarmult8.c
    scalarmult_ed25519.c
    secretbox.c
    secretbox2.c
    secretbox7.c
    secretbox8.c
    secretbox_easy.c
    secretbox_easy2.c
    secretstream.c
    shorthash.c
    sign.c
    siphashx24.c
    sodium_core.c
    sodium_utils.c
    sodium_utils2.c
    sodium_utils3.c
    sodium_version.c
    stream.c
    stream2.c
    stream3.c
    stream4.c
    verify1.c
    xchacha20.c
)

enable_testing()

set(BANG ON)

foreach (test_src ${test_sources})
    get_filename_component(test_name ${test_src} NAME_WE)

    if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/test/default/${test_src}")
        message(STATUS "Downloading ${test_src} ...")

        file(DOWNLOAD
            "https://raw.githubusercontent.com/jedisct1/libsodium/master/test/default/${test_src}"
            "${CMAKE_CURRENT_LIST_DIR}/test/default/${test_src}")
    endif ()

    if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/test/default/${test_name}.exp")
        message(STATUS "Downloading ${test_name}.exp ...")
        
        file(DOWNLOAD
            "https://raw.githubusercontent.com/jedisct1/libsodium/master/test/default/${test_name}.exp"
            "${CMAKE_CURRENT_LIST_DIR}/test/default/${test_name}.exp")
    endif ()

    add_executable(${test_name} ${CMAKE_CURRENT_LIST_DIR}/test/default/${test_src})
    
    if (MSVC)
        target_compile_definitions(${test_name} PRIVATE _CRT_SECURE_NO_WARNINGS)
    endif ()

    if (BANG)
        target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test/quirks)
        target_link_libraries(${test_name} PRIVATE unofficial-sodium::sodium)
        set(BANG OFF)
    else ()
        target_include_directories(
            ${test_name}
            PRIVATE
                ${sodium_INCLUDE_DIR}
                ${CMAKE_CURRENT_LIST_DIR}/test/quirks
        )
        target_link_libraries(${test_name} PRIVATE ${sodium_LIBRARIES})
        set(BANG ON)
    endif ()

    add_custom_command(TARGET ${test_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/test/default/${test_name}.exp"
        $<TARGET_FILE_DIR:${test_name}>)

    add_test(
        NAME ${test_name}
        COMMAND ${test_name}
        WORKING_DIRECTORY $<TARGET_FILE_DIR:${test_name}>
    )
endforeach ()
