#include <stdlib.h>
#include <string.h>

#include <filesystem>
#include <iostream>

#include "TempDirectory.h"

namespace slt {
namespace testutils {

TempDirectory::TempDirectory()
{
  char path[255];
  ::strcpy(path, (std::filesystem::temp_directory_path() / "XXXXXX").c_str());
  if (!mkdtemp(path)) {
    auto msg = ::strerror(errno);
    std::cout << "Could not create temporary directory: " << msg << std::endl;
    throw std::runtime_error(msg);
  }
  _path = std::filesystem::path(path);
    std::cout << "Created temp dir at \"" << path << "\"" << std::endl;
}

TempDirectory::~TempDirectory()
{
  if (_path) {
    std::filesystem::remove_all(*_path);
  }
}

bool TempDirectory::hasPath()
{
  return _path.has_value();
}

std::filesystem::path TempDirectory::getPath()
{
  return *_path;
}

}
}