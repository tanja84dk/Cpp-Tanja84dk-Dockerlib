#include <iostream>
#include <Tanja84dk/Settings.h>
#include <Tanja84dk/WebRequests.h>
#include <Tanja84dk/api.h>
#include <string>
#include <fmt/core.h>
#include <asio.hpp>
#include <nlohmann/json.hpp>
#include <sstream>
#include <map>
#include <cxxopts.hpp>
#include <memory>

inline std::string getStringFromNameJSONArray(nlohmann::ordered_json &jsonArrayObj, const std::string &searchString)
{
    std::string tmp = jsonArrayObj.at(searchString).dump();
    size_t pos1 = tmp.find('"');
    std::string name = tmp.substr(pos1 + 2);
    size_t pos2 = name.find('"');
    name = name.substr(0, pos2);
    return name;
}

struct webDataObj
{
    int length = {};
    std::string header = {};
    std::string data = {};
    int returnCode = {};

    nlohmann::ordered_json jsonOrdered{};

    void clear()
    {
        this->length = {};
        this->header.clear();
        this->data.clear();
        this->returnCode = {};
        this->jsonOrdered.clear();
    }
}; // struct webDataObj

struct WebCacheClient
{
    std::string tmpBuffer = {};
    std::stringstream header{};
    std::stringstream body{};
    std::errc ec;
    std::string dataType{};

    void clear()
    {
        this->tmpBuffer.clear();
        this->header.clear();
        this->body.clear();
        this->ec = {};
        this->dataType.clear();
    }
};

void printJsonPretty(int tabs, const nlohmann::ordered_json &obj)
{
    std::cout << std::setw(tabs) << obj;
    return;
}

int main(int argc, const char *argv[])
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
        fmt::print("Enter the hostname (Default 192.168.196.1): ");
        getline(std::cin, tmpHostname);
        if (tmpHostname.empty())
        {
            tmpHostname = "192.168.196.1";
        };
        configuration.setHost(tmpHostname);
    }
    if (configuration.getPortLenght() <= 1)
    {
        std::string tmpPort;
        fmt::print("Enter the port (Default 2375): ");
        getline(std::cin, tmpPort);
        if (tmpPort.empty())
        {
            tmpPort = "2375";
        };
        configuration.setPort(tmpPort);
    }

    fmt::print("\n"
               "------------------------------\n"
               "        Select Menu\n"
               "------------------------------\n"
               "\n"
               "[1] List Containers\n"
               "[2] Inspect Container\n"
               "[3] Get container logs\n"
               "[4] Start a Container\n"
               "[5] Stop a container\n"
               "[6] Restart a Container\n"
               "[7] Kill a Container\n"
               "[9] Info\n"
               "[99] Exit\n");

    if (httpType == "" || httpPath == "")
    {
        int choice = 0;
        std::string containerName = "";
        fmt::print("Enter the menu number: ");
        std::cin >> choice;
        fmt::print("\n");

        switch (choice)
        {
        case 1:
            httpType = "GET";
            httpPath = Tanja84dk::DockerLib::API::Containers::listAll();
            containersLocalMap.clear();
            break;
        case 2:
            httpType = "GET";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = "/containers/" + containerName + "/json";
            break;
        case 3:
            httpType = "GET";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = "/containers/" + containerName + "/logs?stdout=true&timestamps=true";
            break;
        case 4:
            httpType = "POST";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = Tanja84dk::DockerLib::API::Containers::start(containerName);
            break;
        case 5:
            httpType = "POST";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = Tanja84dk::DockerLib::API::Containers::stop(containerName);
            break;
        case 6:
            httpType = "POST";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = Tanja84dk::DockerLib::API::Containers::restart(containerName);
            break;
        case 7:
            httpType = "POST";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = Tanja84dk::DockerLib::API::Containers::kill(containerName);
            break;
        case 9:
            httpType = "GET";
            httpPath = "/info";
            break;
        case 99:
            return EXIT_SUCCESS;
        default:
            return EXIT_FAILURE;
        }
        containerName = "";
        choice = 0;
    }

    try
    {
        asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        asio::ip::tcp::resolver resolver(io_service);
        asio::ip::tcp::resolver::query query(configuration.getHost(), configuration.getPort());
        asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        asio::ip::tcp::socket socket(io_service);
        asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        asio::streambuf request;

        if (httpType == "GET")
        {
            Tanja84dk::Dockerlib::httpGetRequest(request, configuration.getHost(), httpPath.data());
        }
        else if (httpType == "POST")
        {
            Tanja84dk::Dockerlib::httpPostRequest(request, configuration.getHost(), httpPath.data());
        }
        else if (httpType == "DELETE")
        {
            Tanja84dk::Dockerlib::httpDeleteRequest(request, configuration.getHost(), httpPath.data());
        }
        else if (httpType == "HEAD")
        {
            Tanja84dk::Dockerlib::httpHeadRequest(request, configuration.getHost(), httpPath.data());
        }
        else if (httpType == "PUT")
        {
            Tanja84dk::Dockerlib::httpPutRequest(request, configuration.getHost(), httpPath.data());
        }
        else
        {
            std::cerr << "[ERROR]: " << httpType << " is a unknown HTTP Type.\n";
            return -1;
        }

        // Send the request.
        asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        asio::streambuf response;
        asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cerr << "[ERROR]: Invalid response\n";
            return 1;
        }
        if (status_code != 200 && status_code != 204)
        {
            std::cerr << "[ERROR]: Response returned with status code " << status_code << "\n";
            return 1;
        }

        // Read the response headers, which are terminated by a blank line.
        asio::read_until(socket, response, "\r\n\r\n");

        WebCacheClient WebCache;
        WebCache.clear();
        webDataObj Client;
        Client.clear();

        // Process the response headers.
        std::string header = {};
        while (std::getline(response_stream, header) && header != "\r")
        {
            WebCache.header << header;
        };

        // Write whatever content we already have to output.
        WebCache.body.clear();
        // webdata.clear();
        if (response.size() > 0)
        {
            // webdata << &response;
            WebCache.body << &response;
        }

        // Read until EOF, writing data to output as we go.
        asio::error_code error;
        while (asio::read(socket, response,
                          asio::transfer_at_least(1), error))
        {
            // webdata << &response;
            WebCache.body << &response;
        }
        if (error != asio::error::eof)
        {
            std::cerr << "[ERROR]: ..\n";
        }

        Client.header = WebCache.header.str();
        std::getline(WebCache.body, WebCache.tmpBuffer, '\r');
        Client.length = stoi(WebCache.tmpBuffer, nullptr, 16);
        WebCache.tmpBuffer.clear();
        std::getline(WebCache.body, Client.data, '\r');
        std::getline(WebCache.body, WebCache.tmpBuffer, '\r');
        Client.returnCode = stoi(WebCache.tmpBuffer);
        WebCache.tmpBuffer.clear();

        // fmt::print("{}\n", Client.data);

        try
        {
            Client.jsonOrdered = nlohmann::ordered_json::parse(Client.data);
            // printJsonPretty(4, Client.jsonOrdered);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[JSON ERROR]:" << e.what() << '\n'
                      << '\n';
        }

        if (!Client.jsonOrdered.empty())
        {
            for (auto &element : Client.jsonOrdered)
            {

                std::string e_Name = getStringFromNameJSONArray(element, "Names");
                std::string e_Id = element.at("Id");
                std::string e_Image = element.at("Image");
                std::string e_State = element.at("State");
                std::string e_Status = element.at("Status");
                std::string e_Command = element.at("Command");

                containersLocalMap.insert(std::pair<std::string, std::string>(e_Name, e_Id));

                fmt::print("Container Name: {}\n", e_Name);
                fmt::print(" - ID: {}\n", e_Id);
                fmt::print(" - Image: {}\n", e_Image);
                fmt::print(" - Command: {}\n", e_Command);
                fmt::print(" - State: {}\n", e_State);
                fmt::print(" - Status: {}\n", e_Status);
                std::cout << " - Ports: " << element.at("Ports") << '\n';
                printJsonPretty(2, nlohmann::ordered_json::parse(element.at("Ports").dump()));
                fmt::print("\n");
            }
        }
        else
        {
            fmt::print("{}\n", Client.data);
        }
        WebCache.clear();
        Client.clear();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}