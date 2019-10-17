#pragma once

#include <filesystem>
#include <optional>

namespace slt {
namespace testutils {

class TempDirectory
{
public:
  TempDirectory();
  ~TempDirectory();

  bool hasPath();
  std::filesystem::path getPath();

private:
  std::optional<std::filesystem::path> _path{};
};

}
}