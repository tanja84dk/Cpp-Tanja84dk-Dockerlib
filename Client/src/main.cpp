#include <iostream>
#include <Tanja84dk/dockerlib/settings.h>
#include <Tanja84dk/dockerlib/web_requests.h>
#include <Tanja84dk/dockerlib/api.h>
#include <string>
#include <fmt/core.h>
#include <asio.hpp>
#include <nlohmann/json.hpp>
#include <sstream>
#include <map>
#include <cxxopts.hpp>
#include <memory>

inline std::string get_string_from_name_json_array(nlohmann::ordered_json &json_array_object, const std::string &search_string)
{
  std::string tmp = json_array_object.at(search_string).dump();
  size_t pos1 = tmp.find('"');
  std::string name = tmp.substr(pos1 + 2);
  size_t pos2 = name.find('"');
  name = name.substr(0, pos2);
  return name;
}

struct WebDataObject
{
  int length = {};
  std::string header = {};
  std::string data = {};
  int return_code = {};

  nlohmann::ordered_json json_ordered_object = {};

  void clear()
  {
    this->length = {};
    this->header.clear();
    this->data.clear();
    this->return_code = {};
    this->json_ordered_object.clear();
  }
}; // struct webDataObj

struct WebCacheClient
{
  std::string temp_buffer_ = {};
  std::stringstream header_ = {};
  std::stringstream body_ = {};
  std::errc error_code_ = {};
  std::string data_type_ = {};

  void clear()
  {
    this->temp_buffer_.clear();
    this->header_.clear();
    this->body_.clear();
    this->error_code_ = {};
    this->data_type_.clear();
  }
};

void pretty_print_json(int tabs, const nlohmann::ordered_json &ordered_json_object)
{
  std::cout << std::setw(tabs) << ordered_json_object;
  return;
}

int main(int argc, const char *argv[])
{
  auto &configuration = Tanja84dk::dockerlib::ConfigClass::get_instance();
  std::string http_path_string = {};
  std::string http_type_string = {};
  std::unordered_map<std::string, std::string> containers_local_map = {};

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
        configuration.set_host(result["Host"].as<std::string>());
      }
      if (result.count("Port"))
      {
        configuration.set_port(result["Port"].as<std::string>());
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
      fmt::print("{}\n", options.help());
    }
  }

  if (configuration.get_hostname_length() <= 2)
  {
    std::string tmpHostname;
    fmt::print("Enter the hostname: ");
    getline(std::cin, tmpHostname);
    if (tmpHostname.empty())
    {
      fmt::print("Missing the hostname or ip\n");
      return 1;
    };
    configuration.set_host(tmpHostname);
  }
  if (configuration.get_port_length() <= 1)
  {
    std::string temp_port_string;
    fmt::print("Enter the port (Default 2375): ");
    getline(std::cin, temp_port_string);
    if (temp_port_string.empty())
    {
      temp_port_string = "2375";
    };
    configuration.set_port(temp_port_string);
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

  if (http_type_string == "" || http_path_string == "")
  {
    int choice = 0;
    std::string container_name_string = "";
    fmt::print("Enter the menu number: ");
    std::cin >> choice;
    fmt::print("\n");

    switch (choice)
    {
    case 1:
      http_type_string = "GET";
      http_path_string = Tanja84dk::dockerlib::api::containers::list_all();
      containers_local_map.clear();
      break;
    case 2:
      http_type_string = "GET";
      fmt::print("Enter container name or container ID: ");
      std::cin >> container_name_string;
      http_path_string = Tanja84dk::dockerlib::api::containers::inspect(container_name_string);
      break;
    case 3:
      http_type_string = "GET";
      fmt::print("Enter container name or container ID: ");
      std::cin >> container_name_string;
      http_path_string = "/containers/" + container_name_string + "/logs?stdout=true&timestamps=true";
      break;
    case 4:
      http_type_string = "POST";
      fmt::print("Enter container name or container ID: ");
      std::cin >> container_name_string;
      http_path_string = Tanja84dk::dockerlib::api::containers::start(container_name_string);
      break;
    case 5:
      http_type_string = "POST";
      fmt::print("Enter container name or container ID: ");
      std::cin >> container_name_string;
      http_path_string = Tanja84dk::dockerlib::api::containers::stop(container_name_string);
      break;
    case 6:
      http_type_string = "POST";
      fmt::print("Enter container name or container ID: ");
      std::cin >> container_name_string;
      http_path_string = Tanja84dk::dockerlib::api::containers::restart(container_name_string);
      break;
    case 7:
      http_type_string = "POST";
      fmt::print("Enter container name or container ID: ");
      std::cin >> container_name_string;
      http_path_string = Tanja84dk::dockerlib::api::containers::kill(container_name_string);
      break;
    case 9:
      http_type_string = "GET";
      http_path_string = "/info";
      break;
    case 99:
      return EXIT_SUCCESS;
    default:
      return EXIT_FAILURE;
    }
    container_name_string = "";
    choice = 0;
  }

  try
  {
    asio::io_service io_service;

    // Get a list of endpoints corresponding to the server name.
    asio::ip::tcp::resolver resolver(io_service);
    asio::ip::tcp::resolver::query query(configuration.get_host(), configuration.get_port());
    asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // Try each endpoint until we successfully establish a connection.
    asio::ip::tcp::socket socket(io_service);
    asio::connect(socket, endpoint_iterator);

    // Form the request. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    asio::streambuf request;

    if (http_type_string == "GET")
    {
      Tanja84dk::dockerlib::http_get_request(request, configuration.get_host(), http_path_string.data());
    }
    else if (http_type_string == "POST")
    {
      Tanja84dk::dockerlib::http_post_request(request, configuration.get_host(), http_path_string.data());
    }
    else if (http_type_string == "DELETE")
    {
      Tanja84dk::dockerlib::http_delete_request(request, configuration.get_host(), http_path_string.data());
    }
    else if (http_type_string == "HEAD")
    {
      Tanja84dk::dockerlib::http_head_request(request, configuration.get_host(), http_path_string.data());
    }
    else if (http_type_string == "PUT")
    {
      Tanja84dk::dockerlib::http_put_request(request, configuration.get_host(), http_path_string.data());
    }
    else
    {
      std::cerr << "[ERROR]: " << http_type_string << " is a unknown HTTP Type.\n";
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
    WebDataObject Client;
    Client.clear();

    // Process the response headers.
    std::string header = {};
    while (std::getline(response_stream, header) && header != "\r")
    {
      WebCache.header_ << header;
    };

    // Write whatever content we already have to output.
    WebCache.body_.clear();
    // webdata.clear();
    if (response.size() > 0)
    {
      // webdata << &response;
      WebCache.body_ << &response;
    }

    // Read until EOF, writing data to output as we go.
    asio::error_code error;
    while (asio::read(socket, response,
                      asio::transfer_at_least(1), error))
    {
      // webdata << &response;
      WebCache.body_ << &response;
    }
    if (error != asio::error::eof)
    {
      std::cerr << "[ERROR]: ..\n";
    }

    Client.header = WebCache.header_.str();
    std::getline(WebCache.body_, WebCache.temp_buffer_, '\r');
    Client.length = stoi(WebCache.temp_buffer_, nullptr, 16);
    WebCache.temp_buffer_.clear();
    std::getline(WebCache.body_, Client.data, '\r');
    std::getline(WebCache.body_, WebCache.temp_buffer_, '\r');
    Client.return_code = stoi(WebCache.temp_buffer_);
    WebCache.temp_buffer_.clear();

    try
    {
      Client.json_ordered_object = nlohmann::ordered_json::parse(Client.data);
      // printJsonPretty(4, Client.jsonOrdered);
    }
    catch (const std::exception &e)
    {
      std::cerr << "[JSON ERROR]:" << e.what() << '\n'
                << '\n';
    }

    if (!Client.json_ordered_object.empty())
    {
      for (auto &element : Client.json_ordered_object)
      {

        std::string e_Name = get_string_from_name_json_array(element, "Names");
        std::string e_Id = element.at("Id");
        std::string e_Image = element.at("Image");
        std::string e_State = element.at("State");
        std::string e_Status = element.at("Status");
        std::string e_Command = element.at("Command");

        containers_local_map.insert(std::pair<std::string, std::string>(e_Name, e_Id));

        fmt::print("Container Name: {}\n", e_Name);
        fmt::print(" - ID: {}\n", e_Id);
        fmt::print(" - Image: {}\n", e_Image);
        fmt::print(" - Command: {}\n", e_Command);
        fmt::print(" - State: {}\n", e_State);
        fmt::print(" - Status: {}\n", e_Status);
        std::cout << " - Ports: " << element.at("Ports") << '\n';
        pretty_print_json(2, nlohmann::ordered_json::parse(element.at("Ports").dump()));
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