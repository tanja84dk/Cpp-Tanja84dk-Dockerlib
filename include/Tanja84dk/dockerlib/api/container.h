#ifndef TANJA84DK_DOCKERLIB_API_CONTAINER_H
#define TANJA84DK_DOCKERLIB_API_CONTAINER_H

#include <Tanja84dk/dockerlib/api/datatype.h>

namespace Tanja84dk {
namespace dockerlib {
namespace api {
namespace container {

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

ApiRequest list_all() noexcept;

ApiRequest create_container([[maybe_unused]] const std::string &data = "") noexcept;

ApiRequest list_running_processes(const std::string &container_name_string,
                                  [[maybe_unused]] const std::string &query_arguments_string = "-ef") noexcept;

ApiRequest get_logs(const std::string &container_name_string, [[maybe_unused]] const std::string data = "") noexcept;

ApiRequest get_changes(const std::string &container_name_string) noexcept;

ApiRequest export_container(const std::string &containerName) noexcept;

ApiRequest stats(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") noexcept;

ApiRequest inspect(const std::string &container_name_string) noexcept;

ApiRequest start(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") noexcept;

ApiRequest stop(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") noexcept;

ApiRequest restart(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") noexcept;

ApiRequest kill(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") noexcept;

ApiRequest update_container(const std::string &container_name_string,
                            [[maybe_unused]] const std::string &data = "") noexcept;

ApiRequest rename_container(const std::string &container_name_string,
                            [[maybe_unused]] const std::string data = "") noexcept;

ApiRequest pause(const std::string &contcontainer_name_stringinerName,
                 [[maybe_unused]] const std::string &data = "") noexcept;

ApiRequest unpause(const std::string &container_name_string, [[maybe_unused]] const std::string &data = "") noexcept;

}  // namespace container
}  // namespace api
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_API_CONTAINER_H
