cmake_minimum_required(VERSION 3.0.2)

project(colinear_points)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(NOT MSVC)

add_executable(colinear openGLMain.cpp)

target_link_libraries(colinear ${CONAN_LIBS})