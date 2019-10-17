slt_add_executable(symlink-tree
  SOURCES
    main.cpp
  LINK
    SLT::Symlink
    Boost::program_options
)
