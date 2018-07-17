cmake_minimum_required(VERSION 2.8)

project(brickset CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(GSOAP REQUIRED)


add_subdirectory(brickset)
add_subdirectory(brickset_console)
