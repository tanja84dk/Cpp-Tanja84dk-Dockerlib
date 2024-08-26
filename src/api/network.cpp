#include <Tanja84dk/dockerlib/api/datatype.h>
#include <Tanja84dk/dockerlib/api/network.h>

using namespace Tanja84dk::dockerlib;

const api::ApiRequest api::network::list() noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/networks";
    Client.content_type = "application/json";
    return Client;
}

const api::ApiRequest api::network::inspect(const std::string &network_name_string,
                                            [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/networks/" + network_name_string;
    Client.content_type = "application/json";
    return Client;
}

const api::ApiRequest api::network::remove(const std::string &network_name_string,
                                           [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "DELETE";
    Client.url_path = "/networks/" + network_name_string;
    Client.content_type = "application/json";
    return Client;
}

const api::ApiRequest api::network::create([[maybe_unused]] const std::string &network_name_string,
                                           [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/networks/create";
    Client.content_type = "application/json";
    return Client;
}

const api::ApiRequest api::network::connect_container_to_network(const std::string &network_name_string,
                                                                 const std::string &container_name_string) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/networks/" + network_name_string + "/connect";
    Client.content_type = "application/json";
    nlohmann::json json_object = nlohmann::json::object({{"Container", container_name_string}});
    Client.data = json_object.dump().c_str();
    return Client;
}

const api::ApiRequest api::network::disconnect_container_from_network(const std::string &network_name_string,
                                                                      const std::string &container_name_string,
                                                                      const bool force_disconnect) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/networks/" + network_name_string + "/disconnect";
    Client.content_type = "application/json";
    nlohmann::json json_object =
        nlohmann::json::object({{"Container", container_name_string}, {"Force", force_disconnect}});
    Client.data = json_object.dump().c_str();
    return Client;
}
