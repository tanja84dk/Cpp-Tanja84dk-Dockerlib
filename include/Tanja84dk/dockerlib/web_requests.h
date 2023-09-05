#ifndef TANJA84DK_DOCKERLIB_WEBREQUESTS_H
#define TANJA84DK_DOCKERLIB_WEBREQUESTS_H

#include <Tanja84dk/http/headers.h>

#include "settings.h"

namespace Tanja84dk {
namespace dockerlib {
void http_get_request(asio::streambuf &request, const std::string &host, const std::string &path) {
    Tanja84dk::http::Headers Header_Client;
    Header_Client.set_http_type("GET");
    Header_Client.set_url_path(path);
    Header_Client.set_http_version("HTTP/1.1");
    Header_Client.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    Header_Client.set_host(host);
    Header_Client.set_data_type("application/json");
    Header_Client.set_language("en-US, en;q=0.8, *;q=0.5");
    Header_Client.set_http_keep_state("close");

    Header_Client.generate_header(request);
}

void http_post_request(asio::streambuf &request, const std::string &host, const std::string &path,
                       const std::string &data = "") {
    Tanja84dk::http::Headers Header_Client;
    Header_Client.set_http_type("POST");
    Header_Client.set_url_path(path);
    Header_Client.set_http_version("HTTP/1.1");
    Header_Client.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    Header_Client.set_host(host);
    Header_Client.set_data_type("application/json");
    Header_Client.set_language("en-US, en;q=0.8, *;q=0.5");
    Header_Client.set_http_keep_state("close");
    Header_Client.generate_header(request, data);
    if (data.length() > 0) {
        Header_Client.set_http_request_body(request, data);
    }
}

void http_delete_request(asio::streambuf &request, const std::string &host, const std::string &path,
                         const std::string &data = "") {
    Tanja84dk::http::Headers Header_Client;
    Header_Client.set_http_type("DELETE");
    Header_Client.set_url_path(path);
    Header_Client.set_http_version("HTTP/1.1");
    Header_Client.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    Header_Client.set_host(host);
    Header_Client.set_data_type("application/json");
    Header_Client.set_language("en-US, en;q=0.8, *;q=0.5");
    Header_Client.set_http_keep_state("close");
    Header_Client.generate_header(request, data);
    if (data.length() > 0) {
        Header_Client.set_http_request_body(request, data);
    }
}

void http_head_request(asio::streambuf &request, const std::string &host, const std::string &path) {
    Tanja84dk::http::Headers Header_Client;
    Header_Client.set_http_type("HEAD");
    Header_Client.set_url_path(path);
    Header_Client.set_http_version("HTTP/1.1");
    Header_Client.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    Header_Client.set_host(host);
    Header_Client.set_data_type("application/json");
    Header_Client.set_language("en-US, en;q=0.8, *;q=0.5");
    Header_Client.set_http_keep_state("close");

    Header_Client.generate_header(request);
}

void http_put_request(asio::streambuf &request, const std::string &host, const std::string &path,
                      const std::string &data = "") {
    Tanja84dk::http::Headers Header_Client;
    Header_Client.set_http_type("PUT");
    Header_Client.set_url_path(path);
    Header_Client.set_http_version("HTTP/1.1");
    Header_Client.set_http_user_agent("Tanja84dkDocker/" + Tanja84dk::dockerlib::version_as_string());
    Header_Client.set_host(host);
    Header_Client.set_data_type("application/json");
    Header_Client.set_language("en-US, en;q=0.8, *;q=0.5");
    Header_Client.set_http_keep_state("close");
    Header_Client.generate_header(request, data);
    if (data.length() > 0) {
        Header_Client.set_http_request_body(request, data);
    }
}

}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_WEBREQUESTS_H
