cmake_minimum_required(VERSION 2.8)

project(brickset CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(GSOAP REQUIRED)
find_package(OpenSSL REQUIRED)
add_definitions(-DWITH_OPENSSL)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(brickset)
add_subdirectory(brickset_console)
