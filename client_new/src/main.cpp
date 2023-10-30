#include <Tanja84dk/dockerlib/dockerlib.h>
#include <httplib.h>

#include <iostream>

const char* HOST = "127.0.0.1";
const char* PORT = "80";

int main() {
    auto& configuration = Tanja84dk::dockerlib::ConfigClass::get_instance();

    if (configuration.get_hostname_length() <= 2) {
        std::string temp_hostname_string;
        // get_and_validate_input(temp_hostname_string, "Enter the hostname:");
        if (temp_hostname_string.empty()) {
            std::cerr << "Missing the hostname or ip\n";
            return EXIT_FAILURE;
        };
        configuration.set_host(temp_hostname_string);
    }

    if (configuration.get_port_length() <= 1) {
        std::string temp_port_string;
        // get_and_validate_input(temp_port_string, "Enter the port (Default 2375): ");
        if (temp_port_string.empty()) {
            temp_port_string = "2375";
        };
        configuration.set_port(temp_port_string);

        httplib::Client cli(configuration.get_host(), std::stoi(configuration.get_port()));
        if (auto res = cli.Get("/")) {
            std::cout << "Status: " << res->status << '\n';
            std::cout << "Content-Type: " << res->get_header_value("Content-Type") << '\n';
            std::cout << "Body: " << res->body << '\n';
        } else {
            std::cerr << "Error: " << res.error() << std::endl;
            return EXIT_FAILURE;
        }
    }
}