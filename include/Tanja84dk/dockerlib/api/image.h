#ifndef TANJA84DK_DOCKERLIB_API_IMAGE_H
#define TANJA84DK_DOCKERLIB_API_IMAGE_H

#include <string>

#include "datatype.h"

namespace Tanja84dk {
namespace dockerlib {
namespace api {
namespace image {
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

const ApiRequest list() noexcept;

const ApiRequest inspect(const std::string &image_name, [[maybe_unused]] const std::string &data = "") noexcept;

const ApiRequest history(const std::string &image_name, [[maybe_unused]] const std::string &data = "") noexcept;

const ApiRequest search([[maybe_unused]] const std::string &data = "") noexcept;
}  // namespace image
}  // namespace api
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_API_IMAGE_H
