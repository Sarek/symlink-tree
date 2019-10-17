#include <filesystem>
#include <fstream>
#include <set>
#include <string>

#include <catch2/catch.hpp>

#include "TempDirectory.h"
#include "traversal.h"

using namespace slt;

TEST_CASE("Traverse a directory tree", "[traversal]")
{
  namespace fs = std::filesystem;

  // build a sample directory tree
  testutils::TempDirectory tmpDir;
  REQUIRE(tmpDir.hasPath());

  std::set<std::string> paths;

  auto path1 = tmpDir.getPath() / "a";
  auto path2 = tmpDir.getPath() / "a/b";
  auto file1 = tmpDir.getPath() / "file.dat";
  auto file2 = tmpDir.getPath() / "a/file2.dat";
  auto file3 = tmpDir.getPath() / "a/b/file3.dat";

  paths.insert(path1);
  paths.insert(path2);
  paths.insert(file1);
  paths.insert(file2);
  paths.insert(file3);

  fs::create_directory(path1);
  fs::create_directory(path2);
  std::ofstream file1Stream(file1);
  std::ofstream file2Stream(file2);
  std::ofstream file3Stream(file3);

  std::set<std::string> foundPaths;
  symlink::traverse(tmpDir.getPath(), [&foundPaths](auto path)
    {
      foundPaths.insert(path);
    });

  REQUIRE(paths == foundPaths);
}
