#pragma once

#include <optional>

#include <boost/filesystem.hpp>

namespace slt {
namespace testutils {

class TempDirectory
{
public:
  TempDirectory();
  ~TempDirectory();

  bool hasPath();
  boost::filesystem::path getPath();

private:
  std::optional<boost::filesystem::path> _path{};
};

}
}