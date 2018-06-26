cmake_minimum_required(VERSION 3.9)

project(sweep_rectangle)

add_executable(sweep_rectangle
  IntervalTree.cpp
  IntervalTree.h
  main.cpp
  SweepLineRectangle.cpp
  SweepLineRectangle.h
)
