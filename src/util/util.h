#pragma once

#include <string>
#include <string_view>
#include <optional>

namespace slt {
namespace util {

/**
 * @brief Return a string view without a prefix.
 * 
 * Create and return a string view into a string that excludes a prefix string.
 * 
 * @param prefix The prefix to remove
 * @param data   The string to remove the prefix from
 * @return std::optional Either the resulting string on success, or nothing on error.
 */
std::optional<std::string_view> remove_prefix(const std::string& prefix, const std::string& data);

/**
 * @brief Copy the ownership information from one filesystem entry to another.
 * 
 * @param source The FS entry to copy from
 * @param target The FS entry to copy to
 * @return true when successful
 * @return false when an error occurs
 */
bool copy_ownership(const std::string& source, const std::string& target);

}
}