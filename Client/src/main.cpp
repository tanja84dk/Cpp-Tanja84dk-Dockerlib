#include <iostream>
#include <Tanja84dk/Settings.h>
#include <Tanja84dk/WebRequests.h>
#include <Tanja84dk/parser/container.hpp>
#include <Tanja84dk/parser/image.hpp>
#include <Tanja84dk/api.h>
#include <string>
#include <fmt/core.h>
#include <fmt/format.h>
#include <asio.hpp>
#include <nlohmann/json.hpp>
#include <sstream>
#include <map>
#include <cxxopts.hpp>
#include <memory>
#include "menu.h"

template <typename T>
void getInputAndValidate(T &input, const std::string &message) noexcept
{
    fmt::print("{}", message);
    std::cin >> input;

    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        fmt::print("Invalid input. Please try again.\n");

        fmt::print("{}", message);
        std::cin >> input;
    }
}

/*
inline std::string getStringFromNameJSONArray(nlohmann::ordered_json &jsonArrayObj, const std::string &searchString)
{
    std::string tmp = jsonArrayObj.at(searchString).dump();
    size_t pos1 = tmp.find('"');
    std::string name = tmp.substr(pos1 + 2);
    size_t pos2 = name.find('"');
    name = name.substr(0, pos2);
    return name;
}
*/

struct webDataObj
{
    int length = {};
    std::string header = {};
    std::string data = {};
    int returnCode = {};

    nlohmann::ordered_json jsonOrdered{};

    webDataObj() { this->clear(); };

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

    WebCacheClient() { this->clear(); };

    void clear()
    {
        this->tmpBuffer.clear();
        this->header.clear();
        this->body.clear();
        this->ec = {};
        this->dataType.clear();
    }
};

void printJsonPretty(const nlohmann::ordered_json &obj, int tabs = 2)
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
    WebCacheClient WebCache;
    webDataObj Client;

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
            std::cerr << "Exception: " << e.what() << "\n";
            fmt::print("{}\n", options.help());
        }
    }

    if (configuration.getHostnameLenght() <= 2)
    {
        std::string tmpHostname;
        getInputAndValidate(tmpHostname, "Enter the hostname: ");
        if (tmpHostname.empty())
        {
            fmt::print("Missing the hostname or ip\n");
            return 1;
        };
        configuration.setHost(tmpHostname);
    }
    if (configuration.getPortLenght() < 1)
    {
        std::string tmpPort;
        getInputAndValidate(tmpPort, "Enter the port: ");
        if (tmpPort.empty())
        {
            tmpPort = "2375";
        };
        configuration.setPort(tmpPort);
    }

    Client::Menues::showMain();

    int choiceMainMenu{};
    int choiceSubMenu{};

    getInputAndValidate(choiceMainMenu, "Enter the menu number: ");
    switch (choiceMainMenu)
    {
    case 1:
        Client::Menues::showContainer();
        getInputAndValidate(choiceSubMenu, "Enter the menu number: ");
        break; // Containers
    case 2:
        Client::Menues::showImages();
        getInputAndValidate(choiceSubMenu, "Enter the menu number: ");
        break; // Images
    case 3:
        Client::Menues::showNetworks();
        getInputAndValidate(choiceSubMenu, "Enter the menu number: ");
        break; // Networks
    case 99:
        return 0;
    }

    if ((choiceMainMenu == 1) && (httpType == "" || httpPath == ""))
    {
        std::string containerName = "";
        fmt::print("\n");

        switch (choiceSubMenu)
        {
        case 1:
            httpType = Tanja84dk::DockerLib::API::Containers::listAll().requestType;
            httpPath = Tanja84dk::DockerLib::API::Containers::listAll().urlPath;
            containersLocalMap.clear();
            WebCache.dataType = Tanja84dk::DockerLib::API::Containers::listAll().contentType;
            break;
        case 2:
            getInputAndValidate(containerName, "Enter container name or container ID: ");
            httpType = Tanja84dk::DockerLib::API::Containers::inspect(containerName).requestType;
            httpPath = Tanja84dk::DockerLib::API::Containers::inspect(containerName).urlPath;
            break;
        case 3:
            httpType = "GET";
            getInputAndValidate(containerName, "Enter container name or container ID: ");
            httpPath = "/containers/" + containerName + "/logs?stdout=true&timestamps=true";
            WebCache.dataType = "text";
            break;
        case 4:
            fmt::print("Enter container name or container ID: ");
            getInputAndValidate(containerName, "Enter container name or container ID: ");
            httpType = Tanja84dk::DockerLib::API::Containers::start(containerName).requestType;
            httpPath = Tanja84dk::DockerLib::API::Containers::start(containerName).urlPath;
            break;
        case 5:
            getInputAndValidate(containerName, "Enter container name or container ID: ");
            httpType = Tanja84dk::DockerLib::API::Containers::stop(containerName).requestType;
            httpPath = Tanja84dk::DockerLib::API::Containers::stop(containerName).urlPath;
            WebCache.dataType = "text";
            break;
        case 6:
            getInputAndValidate(containerName, "Enter container name or container ID: ");
            httpType = Tanja84dk::DockerLib::API::Containers::restart(containerName).requestType;
            httpPath = Tanja84dk::DockerLib::API::Containers::restart(containerName).urlPath;
            WebCache.dataType = "text";
            break;
        case 7:
            getInputAndValidate(containerName, "Enter container name or container ID: ");
            httpType = Tanja84dk::DockerLib::API::Containers::kill(containerName).requestType;
            httpPath = Tanja84dk::DockerLib::API::Containers::kill(containerName).urlPath;
            WebCache.dataType = "text";
            break;
        case 9:
            httpType = "GET";
            httpPath = "/info";
            WebCache.dataType = "application/json";
            break;
        case 99:
            return EXIT_SUCCESS;
        default:
            return EXIT_FAILURE;
        }
        containerName = "";
        choiceSubMenu = 0;
    }
    else if ((choiceMainMenu == 2) && (httpType == "" || httpPath == ""))
    {
        switch (choiceSubMenu)
        {
        case 1:
            httpType = Tanja84dk::DockerLib::API::Images::list().requestType;
            httpPath = Tanja84dk::DockerLib::API::Images::list().urlPath;
            WebCache.dataType = "application/json";
            break;
        case 99:
            return EXIT_SUCCESS;
        default:
            return EXIT_FAILURE;
        }
    }

    else if ((choiceMainMenu == 3) && (httpType == "" || httpPath == ""))
    {
        switch (choiceSubMenu)
        {
        case 1:
            httpType = Tanja84dk::DockerLib::API::Networks::list().requestType;
            httpPath = Tanja84dk::DockerLib::API::Networks::list().urlPath;
            WebCache.dataType = Tanja84dk::DockerLib::API::Networks::list().contentType;
            break;
        case 99:
            return EXIT_SUCCESS;
        default:
            return EXIT_FAILURE;
        }
    }
    else
    {
        fmt::print("Wrong main entry.\nPlease restart and try again\n");
        return 1;
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

        struct ParseTest
        {
            std::string dumpHeader = "";
            std::string httpType = "";
            std::string apiVersion = "";
            std::string contentType = "";
            std::string dockerExperimental = "";
            std::string osType = "";
            std::string server = "";
            std::string date = "";
            std::string contentLength = "";
            std::string connection = "";
            std::string transferEncoding = "";
        };

        ParseTest ParserClient;
        std::string headerLine = "";
        while (std::getline(response_stream, headerLine, '\n'))
        {
            if (headerLine.empty() || headerLine == "\r")
            {
                break;
            }

            if (headerLine.back() == '\r')
            {
                headerLine.resize(headerLine.size() - 1);
            }

            std::string delimiter = ": ";
            std::string token = headerLine.substr(0, headerLine.find_first_of(delimiter));

            if (token == "Api-Version")
            {
                ParserClient.apiVersion = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
            }
            else if (token == "Content-Type")
            {
                ParserClient.contentType = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
                WebCache.dataType = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
            }
            else if (token == "Docker-Experimental")
            {
                ParserClient.dockerExperimental = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
            }
            else if (token == "Ostype")
            {
                ParserClient.osType = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
            }
            else if (token == "Server")
            {
                ParserClient.server = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
            }
            else if (token == "Date")
            {
                ParserClient.date = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
            }
            else if (token == "Content-Length")
            {
                ParserClient.contentLength = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
            }
            else if (token == "Transfer-Encoding")
            {
                ParserClient.transferEncoding = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
                std::cout << ParserClient.transferEncoding << '\n';
            }
            else if (token == "Connection")
            {
                ParserClient.connection = headerLine.substr(headerLine.find_first_of(delimiter) + 1).erase(0, 1);
            }
            else
            {
                std::cout << "Ignored Header: " << std::quoted(headerLine) << '\n';
            }
        }

        // Write whatever content we already have to output.
        WebCache.body.clear();
        if (response.size() > 0)
        {
            WebCache.body << &response;
        }

        // Read until EOF, writing data to output as we go.
        asio::error_code error;
        while (asio::read(socket, response,
                          asio::transfer_at_least(1), error))
        {
            WebCache.body << &response;
        }
        if (error != asio::error::eof)
        {
            std::cerr << "[ERROR]: ..\n";
        }

        Client.header = WebCache.header.str();
        if (ParserClient.transferEncoding == "chunked")
        {
            std::getline(WebCache.body, WebCache.tmpBuffer, '\r');
            Client.length = stoi(WebCache.tmpBuffer, nullptr, 16);
            WebCache.tmpBuffer.clear();
        }
        std::getline(WebCache.body, Client.data, '\r');
        std::getline(WebCache.body, WebCache.tmpBuffer, '\r');
        try
        {
            Client.returnCode = stoi(WebCache.tmpBuffer);
            WebCache.tmpBuffer.clear();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        if (WebCache.dataType == "application/json" && httpPath == "/containers/json?all=true")
        {

            try
            {
                Client.jsonOrdered = nlohmann::ordered_json::parse(Client.data);
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
                    Tanja84dk::DockerLib::Parser::TestStruct NewTest;
                    NewTest.parse(element);
                    NewTest.printParsed();
                    fmt::print("\n");
                }
            }
        }
        else if (WebCache.dataType == "application/json" && httpPath == "/containers/portainer/json")
        {
            try
            {
                Client.jsonOrdered = nlohmann::ordered_json::parse(Client.data);
                // printJsonPretty(Client.jsonOrdered, 4);
            }
            catch (const std::exception &e)
            {
                std::cerr << "[JSON ERROR]:" << e.what() << '\n'
                          << '\n';
            }

            if (!Client.jsonOrdered.empty())
            {
                Tanja84dk::DockerLib::Parser::Inspect InspectClient;
                InspectClient.parse(Client.jsonOrdered);

                InspectClient.printParsed();
            }
        }
        else if (WebCache.dataType == "application/json" && httpPath == "/images/json")
        {
            try
            {
                Client.jsonOrdered = nlohmann::ordered_json::parse(Client.data);
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
                    Tanja84dk::DockerLib::Parser::Image::Inspect NewTest;
                    NewTest.parse(element);
                    NewTest.printParsed();
                    fmt::print("\n");
                }
            }
        }
        else
        {
            try
            {
                nlohmann::ordered_json testParse = nlohmann::ordered_json::parse(Client.data);
                printJsonPretty(testParse);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }

            std::string printDataTest;
            response_stream >> printDataTest;
            std::cout << printDataTest << '\n';
            // fmt::print("{}\n", printDataTest);
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