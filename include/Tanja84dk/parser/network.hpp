#ifndef TANJA84DK_DOCKERLIB_PARSER_NETWORK_HPP
#define TANJA84DK_DOCKERLIB_PARSER_NETWORK_HPP

#include <string>
#include <fmt/core.h>
#include <nlohmann/json.hpp>

namespace Tanja84dk::DockerLib::Parser
{
    struct NetworkDataStore
    {
    public:
        friend NetworkInterface;

    private:
        std::string m_Id;
        std::string m_Name;
        std::string m_State;
        std::string m_PortBindings;
        std::string m_Image;
        std::string m_WorkingDir;
        std::string m_Entrypoint;
    };

    struct NetworkInterface : NetworkDataStore
    {
    public:
    private:
    };

}

#endif // TANJA84DK_DOCKERLIB_PARSER_NETWORK_HPP