slt_add_test(SymlinkTest
  SOURCES
    recreate_test.cpp
    traversal_test.cpp
  LINK
    SLT::Tests::Utils
    SLT::Symlink
)