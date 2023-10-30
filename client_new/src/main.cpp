#include <httplib.h>

#include <iostream>

const char* HOST = "127.0.0.1";
const char* PORT = "80";

int main() {
    httplib::Client cli(HOST, std::stoi(PORT));
    if (auto res = cli.Get("/")) {
        std::cout << "Status: " << res->status << '\n';
        std::cout << "Content-Type: " << res->get_header_value("Content-Type") << '\n';
        std::cout << "Body: " << res->body << '\n';
    } else {
        std::cerr << "Error: " << res.error() << std::endl;
        return EXIT_FAILURE;
    }
}