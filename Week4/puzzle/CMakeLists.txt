cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 17)
project(puzzle)

add_executable(Board
  Board.cpp
  Board.h
  BoardMain.cpp
  CountInversions.h
)
