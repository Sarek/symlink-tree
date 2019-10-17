include(CMakeParseArguments)

###
# Add a library target
#
# slt_add_library(
#   SLT:MyLibrary
#   [SOURCES
#     source1.cpp
#     [source2.cpp]]
#   [PUBLIC_LINKING
#     Some::Library
#     [Other::Library]]
#   [STATIC | SHARED]
# )
#
# The function expects the library name as a parameter and
# derives some things from it. E.g., slt_add_library(SLT::MyLibrary)
# produces:
#
#   - a library target named slt_mylibrary with output name
#     (lib)slt-mylibrary(.so)
#   - an alias target named SLT::MyLibrary in global scope
#
# It will automatically add the given SOURCES to the target and
# publicly link the target against the targets given in PUBLIC_LINKING,
# it will privately link against the targets given in PRIVATE_LINKING.
# If STATIC or SHARED are given, the library will be created as such,
# otherwise the configured default is used.
#
# The function exports the TARGET variable which can be used in the
# current scope for further tweaking the target. To refer to the
# target outside of the current scope, e.g., for linking, use the
# alias name.
#
function(slt_add_library _alias)
  set(options SHARED STATIC)
  set(oneValueArgs)
  set(multiValueArgs SOURCES PUBLIC_LINKING PRIVATE_LINKING)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Derive names from the given module name
  set(_target ${_alias})
  string(TOLOWER ${_target} _target)
  string(REPLACE "::" "_" _target ${_target})
  string(REPLACE "_" "-" _output ${_target})

  if (ARG_STATIC OR NOT ENABLE_SHARED)
    set(buildmode STATIC)
  else()
    set(buildmode SHARED)
  endif()


  add_library(${_target} ${buildmode} "")
  add_library(${_alias} ALIAS ${_target})

  target_sources(${_target}
    PRIVATE
      ${ARG_SOURCES}
  )

  target_include_directories(${_target}
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
      ${CMAKE_CURRENT_BINARY_DIR} # for generated files
  )

  target_link_libraries(${_target}
    PUBLIC
      ${ARG_PUBLIC_LINKING}
    PRIVATE
      ${ARG_PRIVATE_LINKING}
  )

  set_target_properties(${_target} PROPERTIES
    OUTPUT_NAME ${_output}
  )

  if (buildmode STREQUAL "SHARED")
    install(TARGETS ${_target}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
  endif()

  set(TARGET ${_target} PARENT_SCOPE)
endfunction(slt_add_library)

###
# Add an executable target
#
# slt_add_executable(name
#   [SOURCES
#     source1.cpp
#     [source2.cpp]]
#   [LINK
#     SLT::MyLibrary
#     [Other::Library]]
#   [OUTPUT_SUFFIX path]
# )
#
# The function expects the executable name as a parameter and will create
# a target of the same name.
# It will add the given SOURCES to that target and private link against
# the targets given in LINK.
# The executable will be placed in the default installation directory,
# suffixed with the OUTPUT_SUFFIX.
#
function(slt_add_executable _name)
  set(options )
  set(oneValueArgs OUTPUT_SUFFIX)
  set(multiValueArgs SOURCES LINK)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  add_executable(${_name})

  target_sources(${_name}
    PRIVATE
      ${ARG_SOURCES}
  )

  target_link_libraries(${_name}
    PRIVATE
      ${ARG_LINK}
  )

  install(TARGETS ${_target}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/${ARG_OUTPUT_SUFFIX}"
  )
endfunction(slt_add_executable)

###
# Define a unit test target that will produce an executable.
#
# slt_add_test(UnitTestName
#   [SOURCES
#     source1.cpp
#     [source2.cpp]]
#   [LINK
#     SLT::MyLibrary
#     [Other::Library]]
# )
#
# The function will define a new executable target with the name
# UnitTestName. It will add the given SOURCES to it and privately
# link against the targets given in LINK. It will also additionally
# link against the target SLT::Tests::Main which is supposed to
# contain the main function.
# The executables will automatically be placed in
# ${CMAKE_INSTALL_BINDIR}/tests
#
function(slt_add_test _name)
  set(options )
  set(multiValueArgs SOURCES LINK)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  list(INSERT ARG_LINK 0 "SLT::Tests::Main")

  slt_add_executable(${_name}
    SOURCES ${ARG_SOURCES}
    LINK ${ARG_LINK}
    OUTPUT_SUFFIX "tests"
  )

  ParseAndAddCatchTests(${_name})
endfunction(slt_add_test)