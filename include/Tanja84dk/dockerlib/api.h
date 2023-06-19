#ifndef TANJA84DK_DOCKERLIB_API_H
#define TANJA84DK_DOCKERLIB_API_H

#include <string>

namespace Tanja84dk::dockerlib::api
{
  namespace containers
  {
    std::string list_all()
    {
      return "/containers/json?all=true";
    }

    std::string inspect(const std::string &container_name_string)
    {
      return "/containers/" + container_name_string + "/json";
    };

    std::string start(const std::string &container_name_string)
    {
      return "/containers/" + container_name_string + "/start";
    }

    std::string stop(const std::string &container_name_string)
    {
      return "/containers/" + container_name_string + "/stop";
    }

    std::string restart(const std::string &container_name_string)
    {
      return "/containers/" + container_name_string + "/restart";
    }

    std::string kill(const std::string &container_name_string)
    {
      return "/containers/" + container_name_string + "/kill";
    }

    std::string pause(const std::string &container_name_string)
    {
      return "/containers/" + container_name_string + "/pause";
    }

    std::string unpause(const std::string &container_name_string)
    {
      return "/containers/" + container_name_string + "/unpause";
    }
  }

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

  namespace images
  {
    std::string list()
    {
      return "/images/json";
    }

    std::string inspect(const std::string &image_name)
    {
      return "/images/" + image_name + "/json";
    }

    std::string history(const std::string &image_name)
    {
      return "/images/" + image_name + "/history";
    }

    std::string search()
    {
      return "/images/search";
    }
  }
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

}

#endif // TANJA84DK_DOCKERLIB_API_H
