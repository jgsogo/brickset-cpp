cmake_minimum_required(VERSION 2.8)
project(MyHello CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# https://github.com/nherbaut/cmake-gsoap-simple-example/tree/master/src

add_library(hello hello.cpp)
