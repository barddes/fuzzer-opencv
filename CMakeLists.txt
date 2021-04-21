cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
project(fuzzer_opencv)

#set(CMAKE_CXX_STANDARD 14)
#set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O1 -fsanitize=fuzzer")

#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(fuzzer_opencv target.cpp png-mutator.cpp png-mutator.h)
#target_link_libraries(fuzzer_opencv ${OpenCV_LIBS})

target_compile_options(fuzzer_opencv
        PRIVATE $<$<C_COMPILER_ID:Clang>:-g -O1 -fsanitize=fuzzer>
        )

target_link_libraries(fuzzer_opencv
        PRIVATE $<$<C_COMPILER_ID:Clang>:-fsanitize=fuzzer>
        )