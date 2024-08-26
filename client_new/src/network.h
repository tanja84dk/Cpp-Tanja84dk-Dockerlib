#pragma once

#include <fmt/core.h>
#include <fmt/format.h>

#include <iostream>

#include "client_parsing.h"

namespace Tanja84dk {
namespace client {
namespace network {
void print(std::string_view data) noexcept;
//[[nodiscard]] std::string_view get_id(const Tanja84dk::client::parsing::ContainerParser &ContainerParser_obj) noexcept
//{return "";};
}  // namespace network
}  // namespace client
}  // namespace Tanja84dk