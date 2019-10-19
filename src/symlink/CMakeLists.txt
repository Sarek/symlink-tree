slt_add_library(SLT::Symlink
  SOURCES
    traversal.cpp
  PRIVATE_LINKING
    Boost::filesystem
    SLT::Util
)
