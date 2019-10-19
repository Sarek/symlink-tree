#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "TempDirectory.h"

namespace slt {
namespace testutils {

namespace fs = boost::filesystem;

TempDirectory::TempDirectory()
{
  char path[255];
  ::strcpy(path, (fs::temp_directory_path() / "XXXXXX").c_str());
  if (!mkdtemp(path)) {
    auto msg = ::strerror(errno);
    std::cout << "Could not create temporary directory: " << msg << std::endl;
    throw std::runtime_error(msg);
  }
  _path = fs::path(path);
    std::cout << "Created temp dir at \"" << path << "\"" << std::endl;
}

TempDirectory::~TempDirectory()
{
  if (_path) {
    fs::remove_all(*_path);
  }
}

bool TempDirectory::hasPath()
{
  return _path.has_value();
}

fs::path TempDirectory::getPath()
{
  return *_path;
}

}
}