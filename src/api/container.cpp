#include <Tanja84dk/dockerlib/api.h>
#include <Tanja84dk/dockerlib/api/container.h>

using namespace Tanja84dk::dockerlib;

api::ApiRequest api::container::list_all() noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/json?all=true";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::create_container([[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/create";
    Client.content_type = "application/json";
    Client.data = data;
    return Client;
}

api::ApiRequest api::container::list_running_processes(
    const std::string &container_name_string, [[maybe_unused]] const std::string &query_arguments_string) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/top";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::get_logs(const std::string &container_name_string,
                                         [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/logs";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::get_changes(const std::string &container_name_string) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/changes";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::export_container(const std::string &container_name_string) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/export";
    Client.content_type = "application/x-tar";
    return Client;
}

api::ApiRequest api::container::stats(const std::string &container_name_string,
                                      [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "containers/" + container_name_string + "/stats";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::inspect(const std::string &container_name_string) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/json";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::start(const std::string &container_name_string,
                                      [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/start";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::stop(const std::string &container_name_string,
                                     [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/stop";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::restart(const std::string &container_name_string,
                                        [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/restart";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::kill(const std::string &container_name_string,
                                     [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/kill";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::update_container(const std::string &container_name_string,
                                                 [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/update";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::rename_container(const std::string &container_name_string,
                                                 [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/rename";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::pause(const std::string &container_name_string,
                                      [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/pause";
    Client.content_type = "application/json";
    return Client;
}

api::ApiRequest api::container::unpause(const std::string &container_name_string,
                                        [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/unpause";
    Client.content_type = "application/json";
    return Client;
}
