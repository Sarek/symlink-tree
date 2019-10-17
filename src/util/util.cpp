#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

#include "util.h"

namespace slt {
namespace util {

std::optional<std::string_view> remove_prefix(const std::string& prefix, const std::string& data)
{
  auto pos = data.find(prefix);

  // Either `prefix` is not in `data` (pos == npos), or it's not a true prefix.
  // In either case, return an empty optional.
  if (pos != 0) {
    return {};
  }

  std::string_view retval(data);
  retval.remove_prefix(prefix.size());

  return retval;
}

bool copy_ownership(const std::string& source, const std::string& target)
{
  struct stat sourceStat;
  errno = 0;
  std::cout << "Copying ownership from " << source << " to " << target << std::endl;

  if (::stat(source.c_str(), &sourceStat) != 0) {
    auto msg = ::strerror(errno);
    std::cout << "Error while retrieving ownership for \"" << source << "\": " << msg << std::endl;
    return false;
  }

  std::cout << "Found UID " << sourceStat.st_uid << ", GID " << sourceStat.st_gid << std::endl;

  errno = 0;
  if (::lchown(target.c_str(), sourceStat.st_uid, sourceStat.st_gid) != 0) {
    auto msg = ::strerror(errno);
    std::cout << "Error while changing ownership for \"" << target << "\": " << msg << std::endl;
    return false;
  }

  return true;
}

}
}