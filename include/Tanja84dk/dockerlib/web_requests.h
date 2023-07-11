#ifndef TANJA84DK_DOCKERLIB_WEBREQUESTS_H
#define TANJA84DK_DOCKERLIB_WEBREQUESTS_H

#include <Tanja84dk/dockerlib/settings.h>
#include <Tanja84dk/http/headers.h>

namespace Tanja84dk {
namespace dockerlib {
void http_get_request(asio::streambuf &request, const std::string &host, const std::string &path) {
    Tanja84dk::Headers HeaderClient;
    HeaderClient.set_http_type("GET");
    HeaderClient.set_url_path(path);
    HeaderClient.set_http_version("HTTP/1.1");
    HeaderClient.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    HeaderClient.set_host(host);
    HeaderClient.set_data_type("application/json");
    HeaderClient.set_language("en-US, en;q=0.8, *;q=0.5");
    HeaderClient.set_http_keep_state("close");

    HeaderClient.generate_header(request);
}

void http_post_request(asio::streambuf &request, const std::string &host, const std::string &path,
                       const std::string &data = "") {
    Tanja84dk::Headers HeaderClient;
    HeaderClient.set_http_type("POST");
    HeaderClient.set_url_path(path);
    HeaderClient.set_http_version("HTTP/1.1");
    HeaderClient.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    HeaderClient.set_host(host);
    HeaderClient.set_data_type("application/json");
    HeaderClient.set_language("en-US, en;q=0.8, *;q=0.5");
    HeaderClient.set_http_keep_state("close");
    HeaderClient.generate_header(request, data);
    if (data.length() > 0) {
        HeaderClient.set_http_request_body(request, data);
    }
}

void http_delete_request(asio::streambuf &request, const std::string &host, const std::string &path,
                         const std::string &data = "") {
    Tanja84dk::Headers HeaderClient;
    HeaderClient.set_http_type("DELETE");
    HeaderClient.set_url_path(path);
    HeaderClient.set_http_version("HTTP/1.1");
    HeaderClient.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    HeaderClient.set_host(host);
    HeaderClient.set_data_type("application/json");
    HeaderClient.set_language("en-US, en;q=0.8, *;q=0.5");
    HeaderClient.set_http_keep_state("close");
    HeaderClient.generate_header(request, data);
    if (data.length() > 0) {
        HeaderClient.set_http_request_body(request, data);
    }
}

void http_head_request(asio::streambuf &request, const std::string &host, const std::string &path) {
    Tanja84dk::Headers HeaderClient;
    HeaderClient.set_http_type("HEAD");
    HeaderClient.set_url_path(path);
    HeaderClient.set_http_version("HTTP/1.1");
    HeaderClient.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    HeaderClient.set_host(host);
    HeaderClient.set_data_type("application/json");
    HeaderClient.set_language("en-US, en;q=0.8, *;q=0.5");
    HeaderClient.set_http_keep_state("close");

    HeaderClient.generate_header(request);
}

void http_put_request(asio::streambuf &request, const std::string &host, const std::string &path,
                      const std::string &data = "") {
    Tanja84dk::Headers HeaderClient;
    HeaderClient.set_http_type("PUT");
    HeaderClient.set_url_path(path);
    HeaderClient.set_http_version("HTTP/1.1");
    HeaderClient.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    HeaderClient.set_host(host);
    HeaderClient.set_data_type("application/json");
    HeaderClient.set_language("en-US, en;q=0.8, *;q=0.5");
    HeaderClient.set_http_keep_state("close");
    HeaderClient.generate_header(request, data);
    if (data.length() > 0) {
        HeaderClient.set_http_request_body(request, data);
    }
}

}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_WEBREQUESTS_H
