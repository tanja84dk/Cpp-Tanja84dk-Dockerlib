#ifndef TANJA84DK_DOCKERLIB_API_H
#define TANJA84DK_DOCKERLIB_API_H

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Tanja84dk {
namespace dockerlib {
namespace api {

struct ApiRequest {
    std::string request_type = {};

    std::string data = {};
    std::string content_type = {};
    std::string url_path = {};

    std::vector<std::string> options = {};

    ApiRequest() { this->clear_all(); }

   private:
    void clear_all() {
        this->request_type.clear();
        this->data.clear();
        this->content_type.clear();
        this->url_path.clear();
        this->options.clear();
    }
};

namespace containers {

/*
 // Containers
 Routes:
  - GET
   - List Containers (/containers/json)
   - List processes running inside a container (/containers/{id}/top)
   - Get container logs (/containers/{id}/logs)
   - Get changes on a container’s filesystem (/containers/{id}/changes)
   - Export a container (/containers/{id}/export)
   - Get container stats based on resource usage (/containers/{id}/stats)
   - Get an archive of a filesystem resource in a container (/v1.41/containers/{id}/archive)
   -

  - POST
   - Create a container (/containers/create)
   - Resize a container TTY (/containers/{id}/resize)
   - Start a container (/containers/{id}/start)
   - Stop a container (/v1.41/containers/{id}/stop)
   - Restart a container (/v1.41/containers/{id}/restart)
   - Kill a container (/v1.41/containers/{id}/kill)
   - Update a container (/v1.41/containers/{id}/update)
   - Rename a container (/v1.41/containers/{id}/rename)
   - Pause a container (/v1.41/containers/{id}/pause)
   - Unpause a container (/v1.41/containers/{id}/unpause)
   - Attach to a container (/v1.41/containers/{id}/attach)
   - Attach to a container via a websocket (/v1.41/containers/{id}/attach/ws)
   - Wait for a container (/v1.41/containers/{id}/wait) // Block until a container stops, then returns the exit code.
   - Delete stopped containers (/v1.41/containers/prune)

 - DELETE
   - Remove a container (/v1.41/containers/{id})

 - HEAD
   - Get information about files in a container (/v1.41/containers/{id}/archive)

 - PUT
   - Extract an archive of files or folders to a directory in a container (/v1.41/containers/{id}/archive)
 */

ApiRequest list_all() {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/json?all=true";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest create_container([[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/create";
    Client.content_type = "application/json";
    Client.data = data;
    return Client;
}

ApiRequest list_running_processes(const std::string &container_name_string,
                                  [[maybe_unused]] const std::string &query_arguments_string = "-ef") {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/top";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest get_logs(const std::string &container_name_string, [[maybe_unused]] const std::string data = "") {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/logs";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest get_changes(const std::string &container_name_string) {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/changes";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest export_container(const std::string &containerName) {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + containerName + "/export";
    Client.content_type = "application/x-tar";
    return Client;
}

ApiRequest stats(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "containers/" + container_name_string + "/stats";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest inspect(const std::string &container_name_string) {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/containers/" + container_name_string + "/json";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest start(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/start";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest stop(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/stop";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest restart(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/restart";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest kill(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/kill";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest update_container(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/update";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest rename_container(const std::string &container_name_string, [[maybe_unused]] const std::string data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/rename";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest pause(const std::string &contcontainer_name_stringinerName, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + contcontainer_name_stringinerName + "/pause";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest unpause(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "POST";
    Client.url_path = "/containers/" + container_name_string + "/unpause";
    Client.content_type = "application/json";
    return Client;
}
}  // namespace containers

namespace images {
/*
// Images
- GET
  - List Images (/v1.41/images/json)
  - Inspect an image (/v1.41/images/{name}/json)
  - Get the history of an image (/v1.41/images/{name}/history)
  - Search images (/v1.41/images/search) // Search for an image on Docker Hub.
  - Export an image (/v1.41/images/{name}/get)
  - Export several images (/v1.41/images/get)

- POST
  - Build an image (/v1.41/build)
  - Delete builder cache (/v1.41/build/prune)
  - Create an image (/v1.41/images/create) // Create an image by either pulling it from a registry or importing it.
  - Push an image (/v1.41/images/{name}/push)
  - Tag an image (/v1.41/images/{name}/tag)
  - Delete unused images (/v1.41/images/prune)
  - Create a new image from a container (/v1.41/commit)
  - Import images (/v1.41/images/load)

- DELETE
  - Remove an image (/v1.41/images/{name})
*/

ApiRequest list() {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/images/json";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest inspect(const std::string &imageName, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/images/" + imageName + "/json";
    Client.content_type = "application/json";
    return Client;
}

ApiRequest history(const std::string &imageName, [[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/images/" + imageName + "/history";
    return Client;
}

ApiRequest search([[maybe_unused]] const std::string &data = "") {
    ApiRequest Client;
    Client.request_type = "GET";
    Client.url_path = "/images/search";
    return Client;
}
}  // namespace images

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
