#ifndef TANJA84DK_DOCKERLIB_SETTINGS_H
#define TANJA84DK_DOCKERLIB_SETTINGS_H
#include "Tanja84dkDocker_pch.h"

namespace Tanja84dk
{
    namespace Dockerlib
    {
        class ConfigClass
        {
        public:
            static ConfigClass &GetInstance()
            {
                static ConfigClass instance;
                return instance;
            };

            static void setHost(std::string const &host) { GetInstance().setHostImpl(host); };
            static char const *getHost() { return GetInstance().m_Host.data(); };
            static std::size_t getHostnameLenght() { return GetInstance().getHostnameLenghtImpl(); };

            static void setPort(std::string const &port) { GetInstance().setPortImpl(port); };
            static char const *getPort() { return GetInstance().m_Port.data(); };
            static std::size_t getPortLenght() { return GetInstance().getPortLengthImpl(); };

            ConfigClass(const ConfigClass &) = delete;
            ConfigClass(ConfigClass &&) = delete;
            ConfigClass &operator=(const ConfigClass &) = delete;
            ConfigClass &operator=(ConfigClass &&) = delete;

        protected:
            ConfigClass() = default;

        private:
            // getter impl
            std::size_t getHostnameLenghtImpl() { return m_Host.length(); };
            std::size_t getPortLengthImpl() { return m_Port.length(); };

            // setter impl
            void setHostImpl(std::string const &host) { m_Host = host; };
            void setPortImpl(std::string const &port) { m_Port = port; };

            // data
            std::string m_Host{};
            std::string m_Port{};
        };

        std::string versionAsString()
        {
            return (std::to_string(Tanja84dkDocker_VERSION_MAJOR) + "." +
                    std::to_string(Tanja84dkDocker_VERSION_MINOR) + "." +
                    std::to_string(Tanja84dkDocker_VERSION_PATCH));
        }

    } // namespace Dockerlib

} // namespace Tanja84dk

#endif // TANJA84DK_DOCKERLIB_SETTINGS_H