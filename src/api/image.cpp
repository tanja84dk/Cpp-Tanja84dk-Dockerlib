#include <Tanja84dk/dockerlib/api/datatype.h>
#include <Tanja84dk/dockerlib/api/image.h>

using namespace Tanja84dk::dockerlib;

const api::ApiRequest api::image::list() noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/images/json";
    Client.content_type = "application/json";
    return Client;
}

const api::ApiRequest api::image::inspect(const std::string &image_name,
                                          [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/images/" + image_name + "/json";
    Client.content_type = "application/json";
    return Client;
}

const api::ApiRequest api::image::history(const std::string &image_name,
                                          [[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/images/" + image_name + "/history";
    return Client;
}

const api::ApiRequest api::image::search([[maybe_unused]] const std::string &data) noexcept {
    api::ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/images/search";
    return Client;
}
