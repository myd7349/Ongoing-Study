cmake_minimum_required(VERSION 3.9)

project(numcpp_example CXX)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(NumCpp CONFIG REQUIRED)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/ReadMe.cpp")
    file(DOWNLOAD
        "https://raw.githubusercontent.com/dpilger26/NumCpp/master/examples/ReadMe/ReadMe.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/ReadMe.cpp"
    )
endif()
    
add_executable(numcpp_example "${CMAKE_CURRENT_BINARY_DIR}/ReadMe.cpp")
target_link_libraries(
    numcpp_example
    PRIVATE
        NumCpp::NumCpp
        #Boost::filesystem
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
)

# References:
# [How to link against boost.system with cmake](https://stackoverflow.com/questions/1065672/how-to-link-against-boost-system-with-cmake)
