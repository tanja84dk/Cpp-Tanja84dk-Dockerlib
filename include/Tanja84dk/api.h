#ifndef TANJA84DK_DOCKERLIB_API_H
#define TANJA84DK_DOCKERLIB_API_H

#include <string>
#include <vector>

namespace Tanja84dk::DockerLib::API
{

  struct APIRequest
  {
    std::string requestType = "";

    std::string data = "";
    std::string contentType = "";
    std::string urlPath = "";

    std::vector<std::string> options;
  };

  namespace Containers
  {
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

    APIRequest listAll([[maybe_unused]] const std::string &data = "")
    /*First string is the http url and the second string is the http type*/
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/containers/json?all=true";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest createContainer([[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/create";
      Client.contentType = "application/json";
      Client.data = data;
      return Client;
    }

    APIRequest inspect(const std::string &containerName)
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/containers/" + containerName + "/json";
      Client.contentType = "application/json";
      return Client;
    };

    APIRequest listRunningProcesses(const std::string &containerName, [[maybe_unused]] const std::string &queryArgs = "-ef")
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/containers/" + containerName + "/top";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest getLogs(const std::string &containerName, [[maybe_unused]] const std::string data = "")
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/containers/" + containerName + "/logs";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest getChanges(const std::string &containerName)
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/containers/" + containerName + "/changes";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest exportContainer(const std::string &containerName)
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/containers/" + containerName + "/export";
      Client.contentType = "application/x-tar";
      return Client;
    }

    APIRequest stats(const std::string &containerName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "containers/" + containerName + "/stats";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest start(const std::string &containerName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/" + containerName + "/start";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest stop(const std::string &containerName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/" + containerName + "/stop";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest restart(const std::string &containerName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/" + containerName + "/restart";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest kill(const std::string &containerName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/" + containerName + "/kill";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest updateContainer(const std::string &containerName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/" + containerName + "/update";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest renameContainer(const std::string &containerName, [[maybe_unused]] const std::string data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/" + containerName + "/rename";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest pause(const std::string &containerName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/" + containerName + "/pause";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest unpause(const std::string &containerName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/containers/" + containerName + "/unpause";
      Client.contentType = "application/json";
      return Client;
    }
  }
  namespace Images
  {
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

    APIRequest list()
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/images/json";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest inspect(const std::string &imageName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/images/" + imageName + "/json";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest history(const std::string &imageName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/images/" + imageName + "/history";
      return Client;
    }

    APIRequest search([[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/images/search";
      return Client;
    }
  }

  namespace Networks
  {
    /*
      // Networks
       - GET
       - POST
       - DELETE
     */

    APIRequest list()
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/networks";
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest inspect(const std::string &networkName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "GET";
      Client.urlPath = "/networks/" + networkName;
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest remove(const std::string &networkName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "DELETE";
      Client.urlPath = "/networks/" + networkName;
      Client.contentType = "application/json";
      return Client;
    }

    APIRequest create([[maybe_unused]] const std::string &networkName, [[maybe_unused]] const std::string &data = "")
    {
      APIRequest Client;
      Client.requestType = "POST";
      Client.urlPath = "/networks/create";
      Client.contentType = "application/json";
      return Client;
    }

    std::string connectContainerToNetwork(const std::string &networkName)
    {
      return "/networks/" + networkName + "/connect";
    }

    std::string disconnectContainerFromNetwork(const std::string &networkName)
    {
      return "/networks/" + networkName + "/disconnect";
    }
  }

}

#endif // TANJA84DK_DOCKERLIB_API_H
