#ifndef TANJA84DK_DOCKERLIB_CLIENT_CLIENT_PARSING_H
#define TANJA84DK_DOCKERLIB_CLIENT_CLIENT_PARSING_H
#include <nlohmann/json.hpp>
#include <string>

namespace Tanja84dk {
namespace client {
namespace parsing {
class ContainerParser {
   public:
    ContainerParser();
    void parse(nlohmann::ordered_json& json_obj) noexcept;
    void print() const noexcept;
    std::string name_string = {};
    std::string id_string = {};
    std::string image_name_string = {};
    std::string network_string = {};
    std::string state_string = {};
    std::string status_string = {};
    std::string command_string = {};

    void list_images() noexcept;
};
}  // namespace parsing
}  // namespace client
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_CLIENT_CLIENT_PARSING_H