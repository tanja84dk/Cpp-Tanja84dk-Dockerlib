#ifndef TANJA84DK_DOCKERLIB_CLIENT_CLIENT_TOOLS_H
#define TANJA84DK_DOCKERLIB_CLIENT_CLIENT_TOOLS_H

#include <nlohmann/json.hpp>

namespace Tanja84dk {
namespace DockerLib {
namespace Client {
class Tools {
   public:
    static nlohmann::ordered_json get_json(const char* data) noexcept;

   protected:
};
}  // namespace Client
}  // namespace DockerLib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_CLIENT_CLIENT_TOOLS_H
