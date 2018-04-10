add_library(catch
  CatchMain.cpp
  catch.hpp
)

target_include_directories(catch
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)