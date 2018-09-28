cmake_minimum_required(VERSION 3.8)

project(ProducerConsumerProblemCpp11 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    if(EXISTS "$ENV{VCPKG_ROOT}/installed/x86-windows/include/pthread.h" AND
       EXISTS "$ENV{VCPKG_ROOT}/installed/x86-windows/lib/pthreadsVC2.lib")
        set(Threads_FOUND ON)
    else()
        set(Threads_FOUND OFF)
    endif()
else()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

if(Threads_FOUND)
    add_definitions(-DFOUND_PTHREADS=1)
else()
    add_definitions(-DFOUND_PTHREADS=0)
endif()

option(ENABLE_LOGGING "Enable logging or not" OFF)

if(ENABLE_LOGGING)
    add_definitions(-DENABLE_LOGGING=1)
else()
    add_definitions(-DENABLE_LOGGING=0)
endif()

add_executable(ProducerConsumerProblemCpp11
    "ProducerConsumerProblemCpp11.cpp"
    "../../../cpp/Stopwatch.cpp")

# Currently, find_package does work with `PThreads` when using vcpkg.
if(Threads_FOUND)
    if(WIN32)
        target_include_directories(ProducerConsumerProblemCpp11 PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/include")
        target_link_libraries(ProducerConsumerProblemCpp11 PRIVATE "$ENV{VCPKG_ROOT}/installed/x86-windows/lib/pthreadsVC2.lib")
        
        add_custom_command(TARGET ProducerConsumerProblemCpp11 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$ENV{VCPKG_ROOT}/installed/x86-windows/bin/pthreadsVC2.dll"
                $<TARGET_FILE_DIR:ProducerConsumerProblemCpp11>)
    else()
        target_link_libraries(ProducerConsumerProblemCpp11 Threads::Threads)
    endif()
endif()

# References:
# https://stackoverflow.com/questions/1620918/cmake-and-libpthread
# https://stackoverflow.com/questions/13067401/cmake-check-that-a-local-file-exists
