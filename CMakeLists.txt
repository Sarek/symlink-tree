cmake_minimum_required(VERSION 3.0.0)
project(symlink-tree VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(BUILD_TESTS "Build unit tests")

find_package(Boost 1.67 COMPONENTS program_options REQUIRED)

include(CTest)
include(SLTMacros)

add_subdirectory(src)

if (WITH_TESTS)
  find_package(Catch2)
  include(ParseAndAddCatchTests)
  add_subdirectory(tests)
endif()
