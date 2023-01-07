#include <iostream>
#include <Tanja84dk/Settings.h>
#include <Tanja84dk/WebRequests.h>
#include <string>
#include <fmt/core.h>
#include <asio.hpp>
#include <nlohmann/json.hpp>
#include <sstream>
#include <map>
#include <cxxopts.hpp>

#define DEFAULT_SERVER "192.168.0.1"
#define DEFAULT_PORT "2375"

class cacheData
{
    std::stringstream data;
};

int main(int argc, char **argv)
{

    auto &configuration = Tanja84dk::Dockerlib::ConfigClass::GetInstance();
    std::string httpPath = {};
    std::string httpType = {};
    std::unordered_map<std::string, std::string> containersLocalMap = {};

    if (argc > 1)
    {
        cxxopts::Options options("Tanja84dkDockerClient", "A small scraped docker client from Tanja84dk using web api\n"
                                                          "If none arguments are given then you would be able to set it in the program\n");
        options.add_options()("H,Host", "Setting the Host", cxxopts::value<std::string>())("P,Port", "Setting the Port", cxxopts::value<std::string>())("h,help", "Print Usage");
        options.allow_unrecognised_options();
        auto result = options.parse(argc, argv);
        try
        {
            if (result.count("help"))
            {
                fmt::print("{}\n", options.help());
                exit(0);
            }
            if (result.count("Host"))
            {
                configuration.setHost(result["Host"].as<std::string>());
            }
            if (result.count("Port"))
            {
                configuration.setPort(result["Port"].as<std::string>());
            }
        }
        catch (const std::exception &e)
        {
            fmt::print("{}\n", options.help());
        }
    }

    if (configuration.getHostnameLenght() <= 2)
    {
        std::string tmpHostname;
        fmt::print("Enter the hostname (Default {}): ", DEFAULT_SERVER);
        getline(std::cin, tmpHostname);
        if (tmpHostname.empty())
        {
            tmpHostname = DEFAULT_SERVER;
        };
        configuration.setHost(tmpHostname);
    }
    if (configuration.getPortLenght() <= 1)
    {
        std::string tmpPort;
        fmt::print("Enter the port (Default {}): ", DEFAULT_PORT);
        getline(std::cin, tmpPort);
        if (tmpPort.empty())
        {
            tmpPort = DEFAULT_PORT;
        };
        configuration.setPort(tmpPort);
    }
    return 0;
}