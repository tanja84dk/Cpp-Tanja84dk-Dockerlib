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
#include <memory>

inline std::string getStringData(const nlohmann::ordered_json &j)
{
    std::string tmp{};
    tmp = j.dump().substr(3, (j.dump().length() - 5));
    return tmp;
}

std::string traverseArrayToString(nlohmann::ordered_json arr, int N)
{
    std::string tmp = {};
    for (int i = 0; i < N; i++)
    {
        tmp = arr[i];
    }
    return tmp;
}

struct webDataObj
{
    int length{};
    std::string data{};
    int returnCode{};

    nlohmann::ordered_json jsonOrdered{};
}; // struct webDataObj

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
        int choice = {};
        std::string containerName{};
        fmt::print("Enter the menu number: ");
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            httpType = "GET";
            httpPath = "/containers/json?all=true";
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
            httpPath = "/containers/" + containerName + "/start";
            break;
        case 5:
            httpType = "POST";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = "/containers/" + containerName + "/stop";
            break;
        case 6:
            httpType = "POST";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = "/containers/" + containerName + "/restart";
            break;
        case 7:
            httpType = "POST";
            fmt::print("Enter container name or container ID: ");
            std::cin >> containerName;
            httpPath = "/containers/" + containerName + "/kill";
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

        // My test of GET function

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

        // Process the response headers.
        std::string header = {};
        std::stringstream headerStream = {};
        while (std::getline(response_stream, header) && header != "\r")
            headerStream << header;
        // std::cout << header << "\n";
        fmt::print("\n");

        // Write whatever content we already have to output.
        std::stringstream webdata = {};
        webdata.clear();
        if (response.size() > 0)
        {
            webdata << &response;
        }

        // Read until EOF, writing data to output as we go.
        asio::error_code error;
        while (asio::read(socket, response,
                          asio::transfer_at_least(1), error))
        {
            webdata << &response;
        }
        if (error != asio::error::eof)
        {
            std::cerr << "[ERROR]: ..\n";
        }

        // std::cout << webdata.str();
        //  return 0;

        webDataObj wb1;
        std::string tmpBuffer;
        std::getline(webdata, tmpBuffer, '\r');
        wb1.length = stoi(tmpBuffer, nullptr, 16);
        tmpBuffer = "";
        std::getline(webdata, wb1.data, '\r');
        std::getline(webdata, tmpBuffer, '\r');
        wb1.returnCode = stoi(tmpBuffer);

        try
        {
            wb1.jsonOrdered = nlohmann::ordered_json::parse(wb1.data);
            // printJsonPretty(4, wb1.jsonOrdered);
        }
        catch (std::exception &e)
        {
            fmt::print("[JSON ERROR]: {}", e.what());
        }

        for (auto &element : wb1.jsonOrdered)
        {

            std::string e_Name = {traverseArrayToString(element.at("Names"), element.at("Names").size()).substr(1, -1)};
            std::string e_Id = {element.at("Id")};
            std::string e_State = {element.at("State")};
            std::string e_Status = {element.at("Status")};
            std::string e_Command = {element.at("Command")};

            containersLocalMap.insert(std::pair<std::string, std::string>(e_Name, e_Id));

            // std::cout << "Container ID: " << element["Id"] << "\tContainer Name: " << element["Names"] << "\tState: " << element["State"] << "\tStatus: " << element["Status"] << "\tCommand: " << element["Command"] << '\n';

            fmt::print("Container Name: {}\n", e_Name);
            fmt::print(" - ID: {}\n", e_Id);
            fmt::print(" - Command: {}\n", e_Command);
            fmt::print(" - State: {}\n", e_State);
            fmt::print(" - Status: {}\n", e_Status);
            std::cout << " - Ports: " << element.at("Ports") << '\n';
            fmt::print("\n");
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}