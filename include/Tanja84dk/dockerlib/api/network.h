#ifndef TANJA84DK_DOCKERLIB_API_NETWORK_H
#define TANJA84DK_DOCKERLIB_API_NETWORK_H

#include <Tanja84dk/dockerlib/api/datatype.h>

#include <string>

namespace Tanja84dk {
namespace dockerlib {
namespace api {

namespace network {
/*
  // Networks
   - GET
   - POST
   - DELETE
 */

const ApiRequest list() noexcept;

const ApiRequest inspect(const std::string &network_name_string,
                         [[maybe_unused]] const std::string &data = "") noexcept;

const ApiRequest remove(const std::string &network_name_string, [[maybe_unused]] const std::string &data = "") noexcept;

const ApiRequest create([[maybe_unused]] const std::string &network_name_string,
                        [[maybe_unused]] const std::string &data = "") noexcept;

const ApiRequest connect_container_to_network(const std::string &network_name_string) noexcept;

const ApiRequest disconnect_container_from_network(const std::string &network_name_string,
                                                   const std::string &container_name_string,
                                                   const bool force_disconnect = false) noexcept;

}  // namespace network

}  // namespace api
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_API_NETWORK_H
