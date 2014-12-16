cmake_minimum_required(VERSION 2.8.4)
project(23heap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(23HEAP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCE_FILES test.cpp)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${23HEAP_INCLUDE_DIR}
)

add_executable(23heap_test ${SOURCE_FILES})

