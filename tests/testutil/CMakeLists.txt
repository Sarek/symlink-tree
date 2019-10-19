slt_add_library(SLT::Tests::Utils
  SOURCES
    TempDirectory.cpp
  PRIVATE_LINKING
    Boost::filesystem
)