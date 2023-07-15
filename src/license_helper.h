#ifndef TANJA84DK_DOCKERLIB_LICENSE_HELPER_H_PRIVATE
#define TANJA84DK_DOCKERLIB_LICENSE_HELPER_H_PRIVATE

#include <string>

namespace Tanja84dk {
namespace dockerlib_private {
void replace_all(std::string &str, const std::string &from, const std::string &to) noexcept {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
}  // namespace dockerlib_private
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_LICENSE_HELPER_H_PRIVATE
