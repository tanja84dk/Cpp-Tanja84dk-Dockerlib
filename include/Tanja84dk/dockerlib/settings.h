#ifndef TANJA84DK_DOCKERLIB_SETTINGS_H
#define TANJA84DK_DOCKERLIB_SETTINGS_H
#include <Tanja84dk/dockerlib/tanja84dk_dockerlib_pch.h>

namespace Tanja84dk {
namespace dockerlib {
class ConfigClass {
   public:
    static ConfigClass &get_instance() {
        static ConfigClass instance;
        return instance;
    };

    static void set_host(const std::string &host) { get_instance().set_host_impl(host); };
    static const char *get_host() { return get_instance().host_string_.data(); };
    static std::size_t get_hostname_length() { return get_instance().get_hostname_length_impl(); };

    static void set_port(const std::string &port) { get_instance().set_port_impl(port); };
    static const char *get_port() { return get_instance().port_string_.data(); };
    static std::size_t get_port_length() { return get_instance().get_port_length_impl(); };

    ConfigClass(const ConfigClass &) = delete;
    ConfigClass(ConfigClass &&) = delete;
    ConfigClass &operator=(const ConfigClass &) = delete;
    ConfigClass &operator=(ConfigClass &&) = delete;

   protected:
    ConfigClass() = default;

   private:
    // getter impl
    std::size_t get_hostname_length_impl() { return host_string_.length(); };
    std::size_t get_port_length_impl() { return port_string_.length(); };

    // setter impl
    void set_host_impl(const std::string &host) noexcept { host_string_ = host; };
    void set_port_impl(const std::string &port) noexcept { port_string_ = port; };

    // data
    std::string host_string_ = {};
    std::string port_string_ = {};
};

const std::string version_as_string() { return tanja84dk_dockerlib_VERSION_STRING; }

}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_SETTINGS_H
