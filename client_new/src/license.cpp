#include "license.h"

#include <fmt/core.h>
#include <fmt/format.h>

#include <string_view>

#include "tanja84dk_dockerclient_httplib_licenses_macro.h"

namespace {
void print_title(const std::string_view title) noexcept {
    fmt::print(
        "---------------------------\n"
        "    {}\n"
        "---------------------------\n",
        title);
};

void replace_all(std::string &str, const std::string &from, const std::string &to) noexcept {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

const std::string get_tanja84dk_dockerlib_license() noexcept {
    std::string license = tanja84dk_dockerlib_LICENSE;
    replace_all(license, ";", "\n");
    return license;
}

const std::string get_fmt_license() noexcept {
    std::string license = fmt_LICENSE;
    replace_all(license, ";", "\n");
    return license;
}

const std::string get_nlohmann_json_license() noexcept {
    std::string license = nlohmann_json_LICENSE;
    replace_all(license, ";", "\n");
    return license;
}

const std::string get_cpp_httplib_license() noexcept {
    std::string license = cpp_httplib_LICENSE;
    replace_all(license, ";", "\n");
    return license;
}

}  // namespace

const std::string Tanja84dk::client::license::dockerlib() noexcept { return get_tanja84dk_dockerlib_license(); };

const std::string Tanja84dk::client::license::fmt() noexcept { return get_fmt_license(); };

const std::string Tanja84dk::client::license::nlohmann_json() noexcept { return get_nlohmann_json_license(); };

const std::string Tanja84dk::client::license::cpp_httplib() noexcept { return get_cpp_httplib_license(); };
