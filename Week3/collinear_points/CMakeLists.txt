cmake_minimum_required(VERSION 3.0.2)

project(collinear_points)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(NOT MSVC)

add_executable(collinear
  BottomUpMergeSort.h
  BruteCollinearPoints.cpp
  BruteCollinearPoints.h
  Draw.cpp
  Draw.h
  Group4Points2D.cpp
  Group4Points2D.h
  Line2D.cpp
  Line2D.h
  Merge.h
  Point2D.cpp
  Point2D.h
  main.cpp
)

target_link_libraries(collinear ${CONAN_LIBS})