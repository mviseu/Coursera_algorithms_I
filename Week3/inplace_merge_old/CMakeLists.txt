cmake_minimum_required(VERSION 3.6)
project(week3_inplace_merge C CXX)

# c++ compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set warnings as errors
macro(set_all_warnings_as_errors target)
    target_compile_options(${target}
      PRIVATE
         -Wall -Werror -Wextra
    )
endmacro()

add_subdirectory(
  external
)

add_library(inplace_merge
  INTERFACE
)

target_sources(inplace_merge
  INTERFACE
    ${PROJECT_SOURCE_DIR}/src/InplaceMerge.h
)

target_include_directories(inplace_merge
  INTERFACE
    src
)

add_executable(inplace_merge_main
  src/main.cpp
)

target_link_libraries(inplace_merge_main
  inplace_merge
)

add_executable(inplace_merge_test
  test/InplaceMergeTest.cpp
)

target_link_libraries(inplace_merge_test
  inplace_merge
  catch
)
