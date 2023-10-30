#include <Tanja84dk/dockerlib/api.h>
#include <Tanja84dk/dockerlib/settings.h>
#include <fmt/core.h>
#include <httplib.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "client_parsing.h"
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

void pretty_print_json(int8_t tabs, const nlohmann::ordered_json &ordered_json_object) {
    std::cout << std::setw(tabs) << ordered_json_object;
    return;
}

int main() {
    auto &configuration = Tanja84dk::dockerlib::ConfigClass::get_instance();
    std::string http_path_string = {};
    std::string http_type_string = {};
    std::string http_data_type_string = {};
    std::unordered_map<std::string, std::string> containers_local_map = {};

    if (configuration.get_hostname_length() <= 2) {
        std::string temp_hostname_string;
        get_and_validate_input(temp_hostname_string, "Enter the hostname:");
        if (temp_hostname_string.empty()) {
            std::cerr << "Missing the hostname or ip\n";
            return EXIT_FAILURE;
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
                http_data_type_string = Tanja84dk::dockerlib::api::container::list_all().content_type;
                break;
            case 2:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::inspect(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::inspect(container_name_string).url_path;
                break;
            case 3:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::get_logs(container_name_string).request_type;
                http_path_string =
                    Tanja84dk::dockerlib::api::container::get_logs(container_name_string).url_path + "?stdout=true";
                // Web_Cache.data_type_ =
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
                // Web_Cache.data_type_ = "text";
                break;
            case 6:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::restart(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::restart(container_name_string).url_path;
                // Web_Cache.data_type_ = "text";
                break;
            case 7:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::kill(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::kill(container_name_string).url_path;
                // Web_Cache.data_type_ = "text";
                break;
            case 9:
                http_type_string = "GET";
                http_path_string = "/info";
                // Web_Cache.data_type_ = "application/json";
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }
        container_name_string.clear();
        sub_menu_choice_int = 0;
    }

    httplib::Client cli(configuration.get_host(), std::stoi(configuration.get_port()));
    if (auto res = cli.Get(http_path_string)) {
        std::cout << "Status: " << res->status << '\n';
        std::cout << "Content-Type: " << res->get_header_value("Content-Type") << '\n';

        if (res->get_header_value("Content-Type") == "application/json") {
            nlohmann::ordered_json json_ordered_object_buffer = {};
            json_ordered_object_buffer.clear();

            json_ordered_object_buffer = nlohmann::ordered_json::parse(res->body);

            pretty_print_json(4, json_ordered_object_buffer);
        } else {
            std::cout << "Body: " << res->body << '\n';
        }
    } else {
        std::cerr << "Error: " << res.error() << std::endl;
        return EXIT_FAILURE;
    }
}
