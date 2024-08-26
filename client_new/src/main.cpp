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
#include "client_tools.h"
#include "license.h"
#include "menu.h"
#include "network.h"

void print_all_licenses() noexcept {
    menus::print_menu_label("tanja84dk_dockerlib/Tanja84dk Docker Client");
    fmt::print("{}\n\n", Tanja84dk::client::license::dockerlib());

    menus::print_menu_label("fmt/fmtlib");
    fmt::print("{}\n\n", Tanja84dk::client::license::fmt());
}

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
    std::cout << std::setw(tabs) << ordered_json_object << '\n';
    return;
}

inline std::string get_string_from_name_json_array(const nlohmann::ordered_json &json_array_object,
                                                   const std::string &search_string) {
    std::string tmp = json_array_object.at(search_string).dump();
    size_t pos1 = tmp.find('"');
    std::string name = tmp.substr(pos1 + 2);
    size_t pos2 = name.find('"');
    name = name.substr(0, pos2);
    return name;
}

void tanja84dk_test_parse(const nlohmann::ordered_json &json_ordered_object) noexcept {
    if (!json_ordered_object.empty()) {
        // fmt::print("\nId\t\tName\n--------------------\n");
        // std::vector<std::pair<std::string, std::string>> id_name_pairs;
        menus::print_colum_label("Id\t\tState\tName");
        for (auto &element : json_ordered_object) {
            std::string e_Name = get_string_from_name_json_array(element, "Names");
            std::string e_Id = element.at("Id");
            std::string e_State = element.at("State");
            std::string e_Image = element.at("Image");

            // id_name_pairs.push_back(
            //     std::make_pair(get_string_from_name_json_array(element, "Names"), element.at("Id")));

            fmt::print("{}\t{}\t{}\n", e_Id.substr(0, 12), e_State, e_Name);
        }
        // fmt::print("Original Done\n\n");

        // std::sort(id_name_pairs.begin(), id_name_pairs.end(), std::less<std::pair<std::string, std::string>>());

        // for (auto &element : id_name_pairs) {
        //     fmt::print("{}\t{}\n", element.second.substr(0, 12), element.first);
        // }
    }
}

int main() {
    auto &configuration = Tanja84dk::dockerlib::ConfigClass::get_instance();
    configuration.set_host("192.168.196.3");
    configuration.set_port("2375");
    std::string http_path_string = {};
    std::string http_type_string = {};
    std::string http_data_type_string = {};
    std::string test_for_list = {};
    std::unordered_map<std::string, std::string> containers_local_map = {};

    httplib::Headers headers = {{"Content-Type", "application/json"}, {"Accept", "application/json"}};

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

    switch (main_menu_choice_int) {
        case menus::main_menu_enum::Containers:
            fmt::print("This is the containers switch menu\n");
            break;
        case menus::main_menu_enum::Images:
            fmt::print("This is the Images switch menu\n");
            break;
        case menus::main_menu_enum::Networks:
            fmt::print("This is the Networks switch menu\n");
            break;
        case menus::main_menu_enum::About:
            fmt::print("This is the about switch menu\n");
            break;
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
                test_for_list = "container_list";
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
                http_data_type_string =
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
                http_data_type_string = "text";
                break;
            case 6:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::restart(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::restart(container_name_string).url_path;
                http_data_type_string = "text";
                break;
            case 7:
                get_and_validate_input(container_name_string, "Enter container name or container ID: ");
                http_type_string = Tanja84dk::dockerlib::api::container::kill(container_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::container::kill(container_name_string).url_path;
                http_data_type_string = "text";
                break;
            case 9:
                http_type_string = "GET";
                http_path_string = "/info";
                http_data_type_string = "application/json";
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }
        container_name_string.clear();
        sub_menu_choice_int = 0;
    } else if (main_menu_choice_int == menus::main_menu_enum::Images) {
        std::string image_name_string = {};
        fmt::print("\n");

        switch (sub_menu_choice_int) {
            case 1:
                http_type_string = Tanja84dk::dockerlib::api::image::list().request_type;
                http_path_string = Tanja84dk::dockerlib::api::image::list().url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::image::list().content_type;
                break;
            case 2:
                get_and_validate_input(image_name_string, "Enter image name or image ID: ");
                http_type_string = Tanja84dk::dockerlib::api::image::inspect(image_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::image::inspect(image_name_string).url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::image::inspect(image_name_string).content_type;
                break;
            case 3:
                get_and_validate_input(image_name_string, "Enter image name or image ID: ");
                http_type_string = Tanja84dk::dockerlib::api::image::history(image_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::image::history(image_name_string).url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::image::history(image_name_string).content_type;
                break;
            case 4:
                get_and_validate_input(image_name_string, "Enter image to search for: ");
                http_type_string = Tanja84dk::dockerlib::api::image::search(image_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::image::search(image_name_string).url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::image::search(image_name_string).content_type;
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }
        image_name_string.clear();
        sub_menu_choice_int = 0;
    } else if (main_menu_choice_int == menus::main_menu_enum::Networks) {
        std::string network_name_string = {};
        std::string container_name_string_test = {};
        std::string data = {};
        fmt::print("\n");

        switch (sub_menu_choice_int) {
            case 1:
                http_type_string = Tanja84dk::dockerlib::api::network::list().request_type;
                http_path_string = Tanja84dk::dockerlib::api::network::list().url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::network::list().content_type;
                break;
            case 2:
                get_and_validate_input(network_name_string, "Enter network name: ");
                http_type_string = Tanja84dk::dockerlib::api::network::inspect(network_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::network::inspect(network_name_string).url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::network::inspect(network_name_string).content_type;
                break;
            case 3:
                get_and_validate_input(network_name_string, "Enter network name: ");
                http_type_string = Tanja84dk::dockerlib::api::network::remove(network_name_string).request_type;
                http_path_string = Tanja84dk::dockerlib::api::network::remove(network_name_string).url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::network::remove(network_name_string).content_type;
                break;
            case 4:
                // Create Network
                http_type_string = "POST";
                http_path_string = "";
                http_data_type_string = "application/json";
                break;
            case 5:
                // Connect a Container to a Network
                get_and_validate_input(network_name_string, "Enter network name: ");
                get_and_validate_input(container_name_string_test, "Enter container name or id: ");
                http_type_string = Tanja84dk::dockerlib::api::network::connect_container_to_network(
                                       network_name_string, container_name_string_test)
                                       .request_type;
                http_path_string = Tanja84dk::dockerlib::api::network::connect_container_to_network(
                                       network_name_string, container_name_string_test)
                                       .url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::network::connect_container_to_network(
                                            network_name_string, container_name_string_test)
                                            .content_type;
                break;
            case 6:
                // Disconnect Container from Network
                get_and_validate_input(network_name_string, "Enter network name: ");
                get_and_validate_input(container_name_string_test, "Enter container name or id: ");
                http_type_string = Tanja84dk::dockerlib::api::network::disconnect_container_from_network(
                                       network_name_string, container_name_string_test)
                                       .request_type;
                http_path_string = Tanja84dk::dockerlib::api::network::disconnect_container_from_network(
                                       network_name_string, container_name_string_test)
                                       .url_path;
                http_data_type_string = Tanja84dk::dockerlib::api::network::disconnect_container_from_network(
                                            network_name_string, container_name_string_test)
                                            .content_type;
                data = Tanja84dk::dockerlib::api::network::disconnect_container_from_network(network_name_string,
                                                                                             container_name_string_test)
                           .data;
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }
        network_name_string.clear();
        sub_menu_choice_int = 0;
    } else if (main_menu_choice_int == menus::main_menu_enum::About) {
        switch (sub_menu_choice_int) {
            case 1:
                break;
            case 2:
                print_all_licenses();
                break;
            case 99:
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }
    }

    httplib::Client cli(configuration.get_host(), std::stoi(configuration.get_port()));
    if (auto res = cli.Get(http_path_string, headers)) {
        std::cout << "Status: " << res->status << '\n';
        std::cout << "Content-Type: " << res->get_header_value("Content-Type") << '\n';

        if (res->get_header_value("Content-Type") == "application/json") {
            if (test_for_list == "container_list") {
                tanja84dk_test_parse(nlohmann::ordered_json::parse(res->body.c_str()));
            } else {
                pretty_print_json(4, Tanja84dk::DockerLib::Client::Tools::get_json(res->body.c_str()));
            }
        } else {
            // std::cout << "Body: " << res->body << '\n';
            Tanja84dk::client::network::print(res->body.c_str());
        }
    } else {
        std::cerr << "Error: " << res.error() << std::endl;
        return EXIT_FAILURE;
    }
}
