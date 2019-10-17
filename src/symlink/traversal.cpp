#include <iostream>

#include "traversal.h"
#include "util.h"

namespace slt {
namespace symlink {

namespace fs = std::filesystem;

void traverse(const std::string& path, std::function<void(std::filesystem::path)> callback)
{
  const auto path_len = path.length();
  for (auto&& p: fs::recursive_directory_iterator(path, fs::directory_options::none)) {
    callback(p);
  }
}

bool recreate(const std::filesystem::path& link_prefix,
              const std::filesystem::path& target_prefix,
              const std::filesystem::path& target)
{
  // Both prefixes must exist, target must exist
  if (   !fs::is_directory(link_prefix)
      || !fs::is_directory(target_prefix)
      || !fs::exists(target)) {
    std::cout << "Preconditions for recreation are not met" << std::endl;
    return false;
  }

  // Get the relative path of the target
  // We need to copy the target path into a string, otherwise the (temporary) copies may get corrupted
  std::string target_string{target};
  auto relative_target_path = util::remove_prefix(target_prefix, target_string);
  if (!relative_target_path) {
    std::cout << "Could not remove prefix \"" << target_prefix << "\" from the path"
              << "\"" << target << "\"" << std::endl;
    return false;
  }

  // If the relative target path starts with the preferred directory separator, remove it.
  // Necessary for the append (/) operation to work as intended.
  if (relative_target_path->front() == fs::path::preferred_separator) {
    relative_target_path->remove_prefix(1);
  }
  // Build the complete link path
  auto absolute_link_path = link_prefix / *relative_target_path;

  if (fs::exists(absolute_link_path)) {
    std::cout << "Entry at \"" << absolute_link_path << "\" already exists" << std::endl;
    return false;
  }

  if (fs::is_directory(target)) {
    try {
      // Recreate directory with the same permissions
      fs::create_directory(absolute_link_path, target);
    } catch(fs::filesystem_error& e) {
      std::cout << "Failed to create directory: " << e.what() << std::endl;
      return false;
    }
  } else {
    try {
      // Create a link to the target with the same permissions
      fs::create_symlink(target, absolute_link_path);
    } catch(fs::filesystem_error& e) {
      std::cout << "Failed to create symlink: " << e.what() << std::endl;
      return false;
    }
  }

  util::copy_ownership(target, absolute_link_path);

  return true;
}

}
}