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

TEST_CASE("Copying ownership from one file to another", "[copy_ownership]")
{
  constexpr uid_t uid = 32767;
  constexpr gid_t gid = 32768;

  testutils::TempDirectory tmpDir;
  REQUIRE(tmpDir.hasPath());

  auto sourcePath = tmpDir.getPath() / "sourcefile.dat";
  auto targetPath = tmpDir.getPath() / "targetfile.dat";

  std::ofstream sourcefile(sourcePath.string());
  sourcefile << "Some data";
  sourcefile.close();

  std::ofstream targetfile(targetPath.string());
  targetfile << "Some data";
  targetfile.close();

  errno = 0;
  REQUIRE(::chown(sourcePath.c_str(), uid, gid) == 0);

  REQUIRE(copy_ownership(sourcePath.string(), targetPath.string()));

  struct stat targetStat;
  REQUIRE(stat(targetPath.c_str(), &targetStat) == 0);
  REQUIRE(targetStat.st_gid == gid);
  REQUIRE(targetStat.st_uid == uid);
}