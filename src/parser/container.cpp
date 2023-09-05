#include "Tanja84dk/dockerlib/parser/container.h"

#include <fmt/core.h>

#include <nlohmann/json.hpp>
#include <string>

using namespace Tanja84dk::dockerlib;
/**
 * @brief Parsing the response from a docker container request
 * 
 * @param ordered_json_object nlohmann::ordered_json object as a reference
 */
void parser::Inspect::parse(const nlohmann::ordered_json &ordered_json_object) noexcept {
    this->set_id_(ordered_json_object.at("Id"));
    this->set_state_(ordered_json_object.at("state").at("Status"));
    this->m_StartedAt = ordered_json_object.at("state").at("StartedAt");
    this->m_FinishedAt = ordered_json_object.at("state").at("FinishedAt");
    this->set_name_(ordered_json_object.at("Name"));
    this->m_Platform = ordered_json_object.at("Platform");
    this->m_AppArmorProfile = ordered_json_object.at("AppArmorProfile");
    this->m_Binds = ordered_json_object.at("HostConfig").at("Binds").dump();
    this->m_NetworkMode = ordered_json_object.at("HostConfig").at("NetworkMode");
    // this->m_Ipv4Address = ordered_json_object.at("NetworkSettings").at("");
    this->m_RestartPolicy = ordered_json_object.at("HostConfig").at("RestartPolicy").at("Name");
    this->m_Hostname = ordered_json_object.at("Config").at("Hostname");
    this->set_image_name_(ordered_json_object.at("Config").at("Image"));
    this->set_working_directory_(ordered_json_object.at("Config").at("WorkingDir"));
    this->set_entry_point_(ordered_json_object.at("Config").at("Entrypoint").dump());
    this->m_Mounts = ordered_json_object.at("Mounts").dump();
    this->m_ConfigDomainname = ordered_json_object.at("Config").at("Domainname");
    this->m_ConfigUser = ordered_json_object.at("Config").at("User");
    this->m_ConfigExposedPorts = ordered_json_object.at("Config").at("ExposedPorts").dump();
    this->m_Tty = ordered_json_object.at("Config").at("Tty");
    this->m_OpenStdin = ordered_json_object.at("Config").at("OpenStdin");
    this->m_Cmd = ordered_json_object.at("Config").at("Cmd").dump();
    this->container_working_directory_string_ = ordered_json_object.at("Config").at("WorkingDir");
}

void parser::Inspect::print_parsed() noexcept {
    fmt::print("Container name: {}\n", this->get_name());
    fmt::print(" - ID: {}\n", this->get_id());
    fmt::print(" - state/Status: {}\n", this->get_state());
    fmt::print(" - Started At: {}\n", this->m_StartedAt);
    fmt::print(" - Finished At: {}\n", this->m_FinishedAt);
    fmt::print(" - Platform: {}\n", this->m_Platform);
    fmt::print(" - AppArmor Profile: {}\n", this->m_AppArmorProfile);
    // fmt::print(" - Exec ID: {}\n", this->m_ExecId);
    fmt::print(" - Binds: {}\n", this->m_Binds);
    fmt::print(" - Network Mode: {}\n", this->m_NetworkMode);
    // fmt::print(" - IPv4 Address: {}\n", this->m_Ipv4Address);

    fmt::print(" - Port Bindings: {}\n", this->get_port_bindings());
    fmt::print(" - Restart Policy: {}\n", this->m_RestartPolicy);
    // fmt::print(" - Auto Remove: {}\n", this->m_AutoRemove);
    fmt::print(" - Mounts: {}\n", this->m_Mounts);
    fmt::print(" - Hostname: {}\n", this->getHostname());
    fmt::print(" - Domainname: {}\n", this->m_ConfigDomainname);
    fmt::print(" - User: {}\n", this->m_ConfigUser);
    fmt::print(" - Exposed Ports: {}\n", this->m_ConfigExposedPorts);
    fmt::print(" - Tty: {}\n", this->m_Tty);
    fmt::print(" - Open Stdin: {}\n", this->m_OpenStdin);
    fmt::print(" - Cmd: {}\n", this->m_Cmd);
    fmt::print(" - image_name: {}\n", this->get_image_name());
    fmt::print(" - Working Directory: {}\n", this->container_working_directory_string_);
    fmt::print(" - Entrypoint: {}\n", this->get_entry_point());
}

void parser::TestStruct::clear() noexcept {
    this->name.clear();
    this->id.clear();
    this->image.clear();
    this->command.clear();
    this->state.clear();
    this->status.clear();
    this->ports.clear();
}

void parser::TestStruct::parse(const nlohmann::ordered_json &ordered_json_object) noexcept {
    this->clear();
    this->name = this->get_name_string_from_json_array(ordered_json_object, "Names");
    this->id = ordered_json_object.at("Id");
    this->image = ordered_json_object.at("Image");
    this->state = ordered_json_object.at("State");
    this->status = ordered_json_object.at("Status");
    this->command = ordered_json_object.at("Command");
    this->ports = ordered_json_object.at("Ports").dump();
}

void parser::TestStruct::print_parsed() noexcept {
    fmt::print("Container name: {}\n", this->name);
    fmt::print(" - ID: {}\n", this->id);
    fmt::print(" - image_name: {}\n", this->image);
    fmt::print(" - Command: {}\n", this->command);
    fmt::print(" - state: {}\n", this->state);
    fmt::print(" - Status: {}\n", this->status);
    fmt::print(" - Ports: {}\n", this->ports);
}
