cmake_minimum_required(VERSION 3.6)
project(week3_questions CXX)

# c++ compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set warnings as errors
macro(set_all_warnings_as_errors target)
  if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${target}
      PRIVATE
       # /W4 /WX
    )
  else()
    target_compile_options(${target}
      PRIVATE
         -Wall -Werror -Wextra
    )
  endif()
endmacro()


add_executable(shuffle_forward_list
  ShuffleForwardList.cpp
)
