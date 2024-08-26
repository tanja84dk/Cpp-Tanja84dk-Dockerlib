#ifndef TANJA84DK_DOCKERLIB_CLIENT_LICENSE_H
#define TANJA84DK_DOCKERLIB_CLIENT_LICENSE_H

#include <string_view>

namespace Tanja84dk {
namespace client {
namespace license {
const std::string dockerlib() noexcept;
const std::string fmt() noexcept;
const std::string nlohmann_json() noexcept;
const std::string cpp_httplib() noexcept;
}  // namespace license
}  // namespace client
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_CLIENT_LICENSE_H