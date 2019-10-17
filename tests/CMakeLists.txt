include(CTest)
enable_testing()

slt_add_library(SLT::Tests::Main
  SOURCES
    main.cpp
  PUBLIC_LINKING
    Catch2::Catch2
  STATIC
)

add_subdirectory(testutil)

add_subdirectory(symlink)
add_subdirectory(util)

