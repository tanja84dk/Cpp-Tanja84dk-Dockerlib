#ifndef TANJA84DK_DOCKERLIB_API_H
#define TANJA84DK_DOCKERLIB_API_H

#include <Tanja84dk/dockerlib/api/container.h>
#include <Tanja84dk/dockerlib/api/datatype.h>
#include <Tanja84dk/dockerlib/api/image.h>

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Tanja84dk {
namespace dockerlib {
namespace api {

namespace networks {
/*
  // Networks
   - GET
   - POST
   - DELETE
 */

ApiRequest list() {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/networks";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest inspect(const std::string &network_name_æstring, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/networks/" + network_name_æstring;
    Client.content_type = "application/json";
    return Client;
}

ApiRequest remove(const std::string &network_name_string, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "DELETE";
    Client.url_path = "/networks/" + network_name_string;
    Client.content_type = "application/json";
    return Client;
}

ApiRequest create([[maybe_unused]] const std::string &network_name_string,
                  [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/networks/create";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest connect_container_to_network(const std::string &network_name_string) {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/networks/" + network_name_string + "/connect";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest disconnect_container_from_network(const std::string &network_name_string,
                                             const std::string &container_name_string,
                                             const bool force_disconnect = false) {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/networks/" + network_name_string + "/disconnect";
    Client.content_type = "application/json";
    nlohmann::json json_object =
        nlohmann::json::object({{"Container", container_name_string}, {"Force", force_disconnect}});
    Client.data = json_object.dump().c_str();
    return Client;
}
}  // namespace networks

}  // namespace api
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_API_H
