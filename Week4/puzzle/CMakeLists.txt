cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 17)
project(puzzle)

add_executable(puzzle
  BinaryHeap.h
  Board.cpp
  Board.h
  CountInversions.h
  Priority.h
  PriorityQueue.h
  SearchNode.cpp
  SearchNode.h
  SearchNodeData.cpp
  SearchNodeData.h
  SearchNodeFactory.cpp
  SearchNodeFactory.h
  SearchNodeHamming.cpp
  SearchNodeHamming.h
  SearchNodeManhattan.cpp
  SearchNodeManhattan.h
  Solver.cpp
  Solver.h
  main.cpp
)
