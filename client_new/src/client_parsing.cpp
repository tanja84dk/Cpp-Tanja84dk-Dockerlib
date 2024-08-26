#include "client_parsing.h"

#include <fmt/core.h>

using namespace Tanja84dk::client::parsing;

namespace internal {
std::string get_string_from_name_json_array(nlohmann::ordered_json &json_array_object,
                                            const std::string &search_string) {
    std::string tmp = json_array_object.at(search_string).dump();
    size_t pos1 = tmp.find('"');
    std::string name = tmp.substr(pos1 + 2);
    size_t pos2 = name.find('"');
    name = name.substr(0, pos2);
    return name;
}
}  // namespace internal

ContainerParser::ContainerParser() {}

void ContainerParser::list_images() noexcept { fmt::print("Test"); }

void ContainerParser::parse(nlohmann::ordered_json &json_obj) noexcept {
    this->name_string = internal::get_string_from_name_json_array(json_obj, "Names");
    this->id_string = json_obj.at("Id");
    this->image_name_string = json_obj.at("Image");
    this->network_string = json_obj.at("NetworkSettings").at("Networks").dump();
    this->state_string = json_obj.at("State");
    this->status_string = json_obj.at("Status");
    this->command_string = json_obj.at("Command");
}

void ContainerParser::print() const noexcept {
    fmt::print("Container Name: {}\n", this->name_string);
    fmt::print(" - ID: {}\n", this->id_string);
    fmt::print(" - Image: {}\n", this->image_name_string);
    fmt::print(" - Network: {}\n", this->network_string);
    fmt::print(" - Command: {}\n", this->command_string);
    fmt::print(" - State: {}\n", this->state_string);
    fmt::print(" - Status: {}\n", this->status_string);
}
