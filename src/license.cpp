#include "Tanja84dk/dockerlib/license.h"

#include <Tanja84dk/http/licenses.h>
#include <fmt/core.h>

#include <string>

#include "Tanja84dk/dockerlib/tanja84dk_dockerlib_licenses_macro.h"
#include "license_helper.h"

using namespace Tanja84dk::dockerlib;
/**
 * @brief Printing the title part of the license
 * 
 * @param title 
 */
void license::print_title_for_licenses(const std::string &title) noexcept {
    fmt::print(
        "---------------------------\n"
        "    {}\n"
        "---------------------------\n",
        title);
}

/**
 * @brief Print all licenses
 * 
 */
void license::print_all_licenses() noexcept {
    Tanja84dk::dockerlib::license::print_title_for_licenses("tanja84dk_dockerlib/Tanja84dk Docker Client");
    fmt::print("{}\n\n", Tanja84dk::dockerlib::license::get_tanja84dk_dockerlib_license());

    Tanja84dk::dockerlib::license::print_title_for_licenses("asio 1.28.0");
    fmt::print("{}\n\n", Tanja84dk::dockerlib::license::get_asio_license());

#ifdef cxxopts_LICENSE
    Tanja84dk::dockerlib::license::print_title_for_licenses("cxxopts 3.1.1");
    fmt::print("{}\n\n", Tanja84dk::dockerlib::license::get_cxxopts_license());
#endif

    Tanja84dk::dockerlib::license::print_title_for_licenses("fmt/fmtlib 10.0.0");
    fmt::print("{}\n\n", Tanja84dk::dockerlib::license::get_fmtlib_license());

    Tanja84dk::dockerlib::license::print_title_for_licenses("nlohmann_json 3.11.2");
    fmt::print("{}\n\n", Tanja84dk::dockerlib::license::get_nlohmann_json_license());

    Tanja84dk::dockerlib::license::print_title_for_licenses("tanja84dk_http 0.1.0");
    fmt::print("{}\n\n", Tanja84dk::dockerlib::license::get_tanja84dk_http());
}

const std::string license::get_asio_license() noexcept { return Tanja84dk::http::Licenses::asio(); }

const std::string license::get_tanja84dk_http() noexcept {
    std::string license = tanja84dk_http_LICENSE;
    Tanja84dk::dockerlib_private::replace_all(license, ";", "\n");
    return license;
}

const std::string license::get_cxxopts_license() noexcept {
#ifdef cxxopts_LICENSE
    std::string license = cxxopts_LICENSE;
    Tanja84dk::dockerlib_private::replace_all(license, ";", "\n");
#else
    std::string license = "";
#endif
    return license;
}

const std::string license::get_fmtlib_license() noexcept {
    std::string license = fmt_LICENSE;
    Tanja84dk::dockerlib_private::replace_all(license, ";", "\n");
    return license;
}

const std::string license::get_nlohmann_json_license() noexcept {
    std::string license = nlohmann_json_LICENSE;
    Tanja84dk::dockerlib_private::replace_all(license, ";", "\n");
    return license;
}

const std::string license::get_tanja84dk_dockerlib_license() noexcept {
    std::string license = tanja84dk_dockerlib_LICENSE;
    Tanja84dk::dockerlib_private::replace_all(license, ";", "\n");
    return license;
}
