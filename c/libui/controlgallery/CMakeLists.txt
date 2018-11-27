cmake_minimum_required(VERSION 3.8)

if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(controlgallery C)

find_package(unofficial-libui CONFIG REQUIRED)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

add_executable(controlgallery "controlgallery.c")

target_link_libraries(controlgallery PRIVATE unofficial::libui::libui)

# https://stackoverflow.com/questions/45724766/how-to-set-c-application-entry-point-to-main-on-windows-using-cmake
# https://stackoverflow.com/questions/2753761/how-do-i-tell-cmake-not-to-create-a-console-window
# https://developercommunity.visualstudio.com/content/problem/46678/cmake-set-subsystem-to-console.html
