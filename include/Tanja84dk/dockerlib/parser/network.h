#ifndef TANJA84DK_DOCKERLIB_PARSER_NETWORK_H
#define TANJA84DK_DOCKERLIB_PARSER_NETWORK_H

#include <nlohmann/json.hpp>
#include <string>

namespace Tanja84dk {
namespace dockerlib {
namespace parser {
class Network_Datastore {
   public:
   protected:
    std::string name_ = {};
    std::string id_string_ = {};
    std::string scope_ = {};
    std::string driver_ = {};
    bool enable_ipv6_bool_ = {};
};

}  // namespace parser
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_PARSER_NETWORK_H
