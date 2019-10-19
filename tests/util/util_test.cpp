#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

#include <boost/filesystem.hpp>
#include <catch2/catch.hpp>

#include "util.h"
#include "TempDirectory.h"

using namespace slt;
using namespace slt::util;
namespace fs = boost::filesystem;

TEST_CASE("Removing prefixes from strings", "[remove_prefix]")
{
  std::string real_prefix("/this/is/a/path");
  std::string wrong_prefix("/not/a/path");
  std::string data("/this/is/a/path/to/somewhere");
  std::string expectation("/to/somewhere");

  REQUIRE( remove_prefix(real_prefix, data) == expectation);
  REQUIRE( !remove_prefix(wrong_prefix, data));
  REQUIRE( !remove_prefix("/a/path", data));
}

TEST_CASE("Regression test", "[remove_prefix]")
{
  REQUIRE( remove_prefix("/tmp/rreocE", "/tmp/rreocE/file_sample.dat"));
}

