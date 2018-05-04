cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 17)
project(puzzle)

add_executable(puzzle
  BinaryHeap.h
  Board.cpp
  Board.h
  CountInversions.h
  PriorityQueue.h
  SearchNode.cpp
  SearchNode.h
  Solver.cpp
  Solver.h
  main.cpp
)
