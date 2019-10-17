#include <filesystem>
#include <fstream>
#include <iostream>

#include <catch2/catch.hpp>

#include "TempDirectory.h"
#include "traversal.h"

using namespace slt;

TEST_CASE("Recreate a directory", "[recreate]")
{
  testutils::TempDirectory tmpDirLink;
  testutils::TempDirectory tmpDirTarget;
  REQUIRE(tmpDirLink.hasPath());
  REQUIRE(tmpDirTarget.hasPath());

  auto target = tmpDirTarget.getPath() / "dir";
  std::filesystem::create_directory(target);

  REQUIRE(symlink::recreate(tmpDirLink.getPath(), tmpDirTarget.getPath(), target));

  auto link = tmpDirLink.getPath() / "dir";
  REQUIRE(std::filesystem::exists(link));
  REQUIRE(std::filesystem::is_directory(link));
}

TEST_CASE("Recreate a file", "[recreate]")
{
  testutils::TempDirectory tmpDirLink;
  testutils::TempDirectory tmpDirTarget;
  REQUIRE(tmpDirLink.hasPath());
  REQUIRE(tmpDirTarget.hasPath());

  auto target = tmpDirTarget.getPath() / "file_sample.dat";
  {
    std::ofstream file(target);
    file.close();
  }

  REQUIRE(symlink::recreate(tmpDirLink.getPath(), tmpDirTarget.getPath(), target));

  auto link = tmpDirLink.getPath() / "file_sample.dat";

  REQUIRE(std::filesystem::exists(link));
  REQUIRE(std::filesystem::is_symlink(link));
}