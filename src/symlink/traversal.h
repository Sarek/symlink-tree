#include <functional>
#include <string>

#include <boost/filesystem.hpp>

#pragma once

namespace slt {
namespace symlink {

/**
 * Traverse a directory recursively depth-first and execute a callback for each entry.
 * 
 * @param[in] path The path to start traversing from
 * @param[in] callback The callback to execute
 */
void traverse(const std::string& path, std::function<void(boost::filesystem::path)> callback);

/**
 * Recreate a filesystem entry in a different prefix.
 * 
 * Recreate a filesystem entry in a different prefix either by creating a symbolic link
 * to the original or doing another appropriate action for the specific entry type.
 * 
 * @param[in] link_prefix The prefix directory where the links should be created
 * @param[in] target_prefix The prefix to remove from the target location for figuring out
 *                          the location for the link
 * @param[in] target The target to recreate
 * 
 * @return \c true on success, \c false otherwise
 */
bool recreate(const boost::filesystem::path& link_prefix,
              const boost::filesystem::path& target_prefix,
              const boost::filesystem::path& target);


/**
 * Create a symbolic link.
 * Create a symbolic link at location \c target that points to \c source.
 * 
 * @param[in] target The path where the real file is located.
 * @param[in] link The path to create the symbolic link at.
 * @return \c true on success, \c false otherwise
 */
bool create_symlink(const boost::filesystem::path& target, const boost::filesystem::path& link);

}
}