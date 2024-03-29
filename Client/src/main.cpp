#include <Tanja84dk/dockerlib/api.h>
#include <Tanja84dk/dockerlib/settings.h>
#include <Tanja84dk/dockerlib/web_requests.h>
#include <fmt/core.h>

#include <asio.hpp>
#include <cxxopts.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

#include "client_settings.h"
#include "menu.h"

template <typename T>
void get_and_validate_input(T &input, const std::string &message) noexcept {
    fmt::print("{}", message);
    std::cin >> input;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        fmt::print("Invalid input. Please try again.\n");

        fmt::print("{}", message);
        std::cin >> input;
    }
}

inline std::string get_string_from_name_json_array(nlohmann::ordered_json &json_array_object,
                                                   const std::string &search_string) {
    std::string tmp = json_array_object.at(search_string).dump();
    size_t pos1 = tmp.find('"');
    std::string name = tmp.substr(pos1 + 2);
    size_t pos2 = name.find('"');
    name = name.substr(0, pos2);
    return name;
}

class WebDataObject {
   public:
    int length = {};
    std::string header = {};
    std::string data = {};
    int return_code = {};

    nlohmann::ordered_json json_ordered_object = {};

    void clear() {
        this->length = {};
        this->header.clear();
        this->data.clear();
        this->return_code = {};
        this->json_ordered_object.clear();
    }
};  // class webDataObj

class WebCacheClient {
   public:
    std::string temp_buffer_ = {};
    std::stringstream header_ = {};
    std::stringstream body_ = {};
    std::errc error_code_ = {};
    std::string data_type_ = {};

    void clear() {
        this->temp_buffer_.clear();
        this->header_.clear();
        this->body_.clear();
        this->error_code_ = {};
        this->data_type_.clear();
    }
};  // class WebCacheClient

void pretty_print_json(int8_t tabs, const nlohmann::ordered_json &ordered_json_object) {
    std::cout << std::setw(tabs) << ordered_json_object;
    return;
}

int main(int argc, const char *argv[]) {
    auto &configuration = Tanja84dk::dockerlib::ConfigClass::get_instance();
    std::string http_path_string = {};
    std::string http_type_string = {};
    std::unordered_map<std::string, std::string> containers_local_map = {};
    WebCacheClient Web_Cache;

    if (argc > 1) {
        cxxopts::Options options("Tanja84dkDockerClient",
                                 "A small scraped docker client from Tanja84dk using web api\n"
                                 "If none arguments are given then you would be able to set it in the program\n");
        options.add_options()("H,Host", "Setting the Host", cxxopts::value<std::string>())(
            "P,Port", "Setting the Port", cxxopts::value<std::string>())("h,help", "Print Usage")(
            "l,license", "Printing the licenses");
        options.allow_unrecognised_options();
        auto result = options.parse(argc, argv);
        try {
            if (result.count("help")) {
                fmt::print("{}\n", options.help());
                exit(0);
            }
            if (result.count("license")) {
                Tanja84dk::dockerlib::license::print_all_licenses();
                return 0;
            }
            if (result.count("Host")) {
                configuration.set_host(result["Host"].as<std::string>());
            }
            if (result.count("Port")) {
                configuration.set_port(result["Port"].as<std::string>());
            }
        } catch (const std::exception &e) {
            std::cerr << "Exception: " << e.what() << "\n";
            fmt::print("{}\n", options.help());
        }
    }

    if (configuration.get_hostname_length() <= 2) {
        std::string temp_hostname_string;
        get_and_validate_input(temp_hostname_string, "Enter the hostname:");
        if (temp_hostname_string.empty()) {
            fmt::print("Missing the hostname or ip\n");
            return 1;
        };
        configuration.set_host(temp_hostname_string);
    }

    if (configuration.get_port_length() <= 1) {
        std::string temp_port_string;
        get_and_validate_input(temp_port_string, "Enter the port (Default 2375): ");
        if (temp_port_string.empty()) {
            temp_port_string = "2375";
        };
        configuration.set_port(temp_port_string);
    }

    menus::print_main_menu();

    int main_menu_choice_int = {};
    int sub_menu_choice_int = {};

    get_and_validate_input(main_menu_choice_int, "Enter the menu number: ");
    switch (main_menu_choice_int) {
        case 1:
            menus::print_container_menu();
            get_and_validate_input(sub_menu_choice_int, "Enter the menu number: ");
            break;  // Containers
        case 2:
            menus::print_images_menu();
            get_and_validate_input(sub_menu_choice_int, "Enter the menu number: ");
            break;  // Images
        case 3:
            menus::print_networks_menu();
            get_and_validate_input(sub_menu_choice_int, "Enter the menu number: ");
            break;  // Networks
        case 9:
            menus::print_about_menu();
            get_and_validate_input(sub_menu_choice_int, "Enter the menu number: ");
            break;
        case 99:
            return 0;
    }

    if (main_menu_choice_int == menus::main_menu_enum::Containers) {
        std::string container_name_string = {};
        fmt::print("\n");

        switch (sub_menu_choice_int) {
            case 1:
                http_type_string = Tanja84dk::dockerlib::api::container::list_all().request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::list_all().url_path;
                containers_local_map.clear();
                Web_Cache.data_type_ = Tanja84dk::dockerlib::api::container::list_all().content_type;
                break;
            case 2:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::inspect(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::inspect(container_name_string).url_path;
                break;
            case 3:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::get_logs(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::get_logs(container_name_string).url_path;
                Web_Cache.data_type_ =
                    Tanja84dk::dockerlib::api::container::get_logs(container_name_string).content_type;
                break;
            case 4:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::start(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::start(container_name_string).url_path;
                break;
            case 5:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::stop(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::stop(container_name_string).url_path;
                Web_Cache.data_type_ = "text";
                break;
            case 6:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::restart(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::restart(container_name_string).url_path;
                Web_Cache.data_type_ = "text";
                break;
            case 7:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::kill(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::kill(container_name_string).url_path;
                Web_Cache.data_type_ = "text";
                break;
            case 9:
                http_type_string = "GET";
                http_path_string = "/info";
                Web_Cache.data_type_ = "application/json";
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }
        container_name_string.clear();
        sub_menu_choice_int = 0;
    } else if (main_menu_choice_int == menus::main_menu_enum::Images) {
        switch (sub_menu_choice_int) {
            case 1:
                http_type_string = Tanja84dk::dockerlib::api::image::list().request_type;
                http_path_string = Tanja84dk::dockerlib::api::image::list().url_path;
                Web_Cache.data_type_ = "application/json";
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }
    }

    else if (main_menu_choice_int == menus::main_menu_enum::Networks) {
        switch (sub_menu_choice_int) {
            case 1:
                http_type_string = Tanja84dk::dockerlib::api::network::list().request_type;
                http_path_string = Tanja84dk::dockerlib::api::network::list().url_path;
                Web_Cache.data_type_ = Tanja84dk::dockerlib::api::network::list().content_type;
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }

    } else if (main_menu_choice_int == menus::main_menu_enum::About) {
        switch (sub_menu_choice_int) {
            case 1:
                break;
            case 2:
                Tanja84dk::dockerlib::license::print_all_licenses();
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }

        main_menu_choice_int = 0;
        sub_menu_choice_int = 0;
    } else {
        fmt::print("Wrong main entry.\nPlease restart and try again\n");
        return 1;
    }

    try {
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

        if (http_type_string == "GET") {
            Tanja84dk::dockerlib::http_get_request(request, configuration.get_host(), http_path_string.data());
        } else if (http_type_string == "POST") {
            Tanja84dk::dockerlib::http_post_request(request, configuration.get_host(), http_path_string.data());
        } else if (http_type_string == "DELETE") {
            Tanja84dk::dockerlib::http_delete_request(request, configuration.get_host(), http_path_string.data());
        } else if (http_type_string == "HEAD") {
            Tanja84dk::dockerlib::http_head_request(request, configuration.get_host(), http_path_string.data());
        } else if (http_type_string == "PUT") {
            Tanja84dk::dockerlib::http_put_request(request, configuration.get_host(), http_path_string.data());
        } else {
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
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            std::cerr << "[ERROR]: Invalid response\n";
            return 1;
        }
        if (status_code != 200 && status_code != 204) {
            std::cerr << "[ERROR]: Response returned with status code " << status_code << "\n";
            return 1;
        }

        // Read the response headers, which are terminated by a blank line.
        asio::read_until(socket, response, "\r\n\r\n");

        // WebCacheClient WebCache;
        Web_Cache.clear();
        WebDataObject Client;
        Client.clear();

        // Process the response headers.
        std::string header = {};
        while (std::getline(response_stream, header) && header != "\r") {
            Web_Cache.header_ << header;
        };

        // Write whatever content we already have to output.
        Web_Cache.body_.clear();
        if (response.size() > 0) {
            Web_Cache.body_ << &response;
        }

        // Read until EOF, writing data to output as we go.
        asio::error_code error;
        while (asio::read(socket, response, asio::transfer_at_least(1), error)) {
            Web_Cache.body_ << &response;
        }
        if (error != asio::error::eof) {
            std::cerr << "[ERROR]: ..\n";
        }

        Client.header = Web_Cache.header_.str();
        std::getline(Web_Cache.body_, Web_Cache.temp_buffer_, '\r');
        Client.length = std::stoi(Web_Cache.temp_buffer_, nullptr, 16);
        Web_Cache.temp_buffer_.clear();
        std::getline(Web_Cache.body_, Client.data, '\r');
        std::getline(Web_Cache.body_, Web_Cache.temp_buffer_, '\r');
        Client.return_code = std::stoi(Web_Cache.temp_buffer_);
        Web_Cache.temp_buffer_.clear();

        try {
            Client.json_ordered_object = nlohmann::ordered_json::parse(Client.data);
            // printJsonPretty(4, Client.jsonOrdered);
        } catch (const std::exception &e) {
            std::cerr << "[JSON ERROR]:" << e.what() << '\n' << '\n';
        }

        if (!Client.json_ordered_object.empty()) {
            for (auto &element : Client.json_ordered_object) {
                std::string e_Name = get_string_from_name_json_array(element, "Names");
                std::string e_Id = element.at("Id");
                std::string e_Image = element.at("Image");
                std::string e_Network = element.at("NetworkSettings").at("Networks").dump();
                std::string e_State = element.at("State");
                std::string e_Status = element.at("Status");
                std::string e_Command = element.at("Command");

                containers_local_map.emplace(std::pair<std::string, std::string>(e_Name, e_Id));

                fmt::print("Container Name: {}\n", e_Name);
                fmt::print(" - ID: {}\n", e_Id);
                fmt::print(" - Image: {}\n", e_Image);
                fmt::print(" - Network: {}\n", e_Network);
                fmt::print(" - Command: {}\n", e_Command);
                fmt::print(" - State: {}\n", e_State);
                fmt::print(" - Status: {}\n", e_Status);
                std::cout << " - Ports: " << element.at("Ports").items() << '\n';
                pretty_print_json(2, nlohmann::ordered_json::parse(element.at("Ports").dump()));
                pretty_print_json(2,
                                  nlohmann::ordered_json::parse(element.at("NetworkSettings").at("Networks").dump()));
                fmt::print("\n");
            }
        } else {
            fmt::print("{}\n", Client.data);
        }
        Web_Cache.clear();
        Client.clear();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
