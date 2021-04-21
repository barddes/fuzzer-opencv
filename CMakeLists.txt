cmake_minimum_required(VERSION 3.19)
project(fuzzer_opencv)

set(CMAKE_CXX_STANDARD 14)

add_executable(fuzzer_opencv
        target.cpp png-mutator.cpp png-mutator.h)
