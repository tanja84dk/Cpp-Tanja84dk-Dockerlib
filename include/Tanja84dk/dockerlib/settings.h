#ifndef TANJA84DK_DOCKERLIB_SETTINGS_H
#define TANJA84DK_DOCKERLIB_SETTINGS_H
#include <Tanja84dk/dockerlib/tanja84dk_dockerlib_pch.h>

namespace Tanja84dk
{
  namespace dockerlib
  {
    class ConfigClass
    {
    public:
      static ConfigClass &get_instance()
      {
        static ConfigClass instance;
        return instance;
      };

      static void set_host(std::string const &host) { get_instance().set_host_impl(host); };
      static char const *get_host() { return get_instance().host_string_.data(); };
      static std::size_t get_hostname_length() { return get_instance().get_hostname_length_impl(); };

      static void set_port(std::string const &port) { get_instance().set_port_impl(port); };
      static char const *get_port() { return get_instance().port_string_.data(); };
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
      void set_host_impl(std::string const &host) { host_string_ = host; };
      void set_port_impl(std::string const &port) { port_string_ = port; };

      // data
      std::string host_string_{};
      std::string port_string_{};
    };

    std::string version_as_string()
    {
      return (std::to_string(tanja84dk_dockerlib_VERSION_MAJOR) + "." +
              std::to_string(tanja84dk_dockerlib_VERSION_MINOR) + "." +
              std::to_string(tanja84dk_dockerlib_VERSION_PATCH));
    }

  } // namespace Dockerlib

} // namespace Tanja84dk

#endif // TANJA84DK_DOCKERLIB_SETTINGS_H
