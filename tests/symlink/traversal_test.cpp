#include <fstream>
#include <set>
#include <string>

#include <boost/filesystem.hpp>
#include <catch2/catch.hpp>

#include "TempDirectory.h"
#include "traversal.h"

using namespace slt;

TEST_CASE("Traverse a directory tree", "[traversal]")
{
  namespace fs = boost::filesystem;

  // build a sample directory tree
  testutils::TempDirectory tmpDir;
  REQUIRE(tmpDir.hasPath());

  std::set<fs::path> paths;

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
  std::ofstream file1Stream(file1.string());
  std::ofstream file2Stream(file2.string());
  std::ofstream file3Stream(file3.string());

  std::set<fs::path> foundPaths;
  std::string tmpDirString{tmpDir.getPath().string()};
  symlink::traverse(tmpDirString, [&foundPaths](auto path)
    {
      foundPaths.insert(path);
    });

  REQUIRE(paths == foundPaths);
}
