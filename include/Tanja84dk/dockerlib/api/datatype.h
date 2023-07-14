#ifndef TANJA84DK_DOCKERLIB_API_DATATYPE_H
#define TANJA84DK_DOCKERLIB_API_DATATYPE_H

#include <string>
#include <vector>

namespace Tanja84dk {
namespace dockerlib {
namespace api {

class ApiRequest {
   public:
    std::string request_type = {};

    std::string data = {};
    std::string content_type = {};
    std::string url_path = {};

    std::vector<std::string> options = {};

    ApiRequest() { this->clear_all(); }

    void clear_all() noexcept;
};
}  // namespace api
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_API_DATATYPE_H
