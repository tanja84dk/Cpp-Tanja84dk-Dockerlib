#ifndef TANJA84DK_DOCKERLIB_LICENSE_H
#define TANJA84DK_DOCKERLIB_LICENSE_H

#include <string>

namespace Tanja84dk {
namespace dockerlib {
namespace license {

void print_title_for_licenses(const std::string &title) noexcept;
void print_all_licenses() noexcept;

const std::string get_asio_license() noexcept;
const std::string get_cxxopts_license() noexcept;
const std::string get_tanja84dk_dockerlib_license() noexcept;
const std::string get_tanja84dk_http() noexcept;
const std::string get_fmtlib_license() noexcept;
const std::string get_nlohmann_json_license() noexcept;

}  // namespace license
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_LICENSE_H
