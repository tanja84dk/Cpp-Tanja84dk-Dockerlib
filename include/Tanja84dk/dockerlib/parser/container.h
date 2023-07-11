#ifndef TANJA84DK_DOCKERLIB_PARSER_CONTAINER_H
#define TANJA84DK_DOCKERLIB_PARSER_CONTAINER_H

#include <fmt/core.h>

#include <nlohmann/json.hpp>
#include <string>

namespace Tanja84dk {
namespace DockerLib {
namespace Parser {

struct ContainersDataStore {
    friend struct ContainersInterface;
    virtual void parse([[maybe_unused]] const nlohmann::ordered_json &ordered_json_object) = 0;

   private:
    std::string container_id_string_;
    std::string container_name_string_;
    std::string container_state_string_;
    std::string container_port_bindings_string_;
    std::string container_image_string_;
    std::string container_working_directory_string_;
    std::string container_entry_point_string_;
};

struct ContainersInterface : ContainersDataStore {
    friend struct Inspect;
    virtual void parse([[maybe_unused]] const nlohmann::ordered_json &ordered_json_object) = 0;
    virtual void print_parsed() = 0;

    // Getters
    inline const std::string get_id() noexcept { return this->container_id_string_; };
    inline const std::string get_name() noexcept { return this->container_name_string_; };
    inline const std::string get_state() noexcept { return this->container_state_string_; };
    inline const std::string get_port_bindings() noexcept { return this->container_port_bindings_string_; };
    inline const std::string get_image_name() noexcept { return this->container_image_string_; };
    inline const std::string get_working_directory() noexcept { return this->container_working_directory_string_; };
    inline const std::string get_entry_point() noexcept { return this->container_entry_point_string_; };

   private:
    // Setters
    inline void set_id_(const std::string &id) noexcept { this->container_id_string_ = id; };
    inline void set_name_(const std::string &name) noexcept { this->container_name_string_ = name; };
    inline void set_state_(const std::string &state) noexcept { this->container_state_string_ = state; };
    inline void set_port_bindings_(const std::string &port_bindings) noexcept {
        this->container_port_bindings_string_ = port_bindings;
    };
    inline void set_image_name_(const std::string &image_name) noexcept { this->container_image_string_ = image_name; };
    inline void set_working_directory_(const std::string &working_directory) noexcept {
        this->container_working_directory_string_ = working_directory;
    };
    inline void set_entry_point_(const std::string &entry_point) noexcept {
        this->container_entry_point_string_ = entry_point;
    };
};

struct Inspect : ContainersInterface {
    void parse(const nlohmann::ordered_json &ordered_json_object) noexcept override {
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
    };

    /// @brief Printing the parsed data from the Docker API response
    inline void print_parsed() noexcept override {
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

    // Getters
    inline const std::string getStartedAt() noexcept { return this->m_StartedAt; };
    inline const std::string getFinishedAt() noexcept { return this->m_FinishedAt; };
    inline const std::string getPlatform() noexcept { return this->m_Platform; };
    inline const std::string getAppArmorProfile() noexcept { return this->m_AppArmorProfile; };
    inline const std::string getBinds() noexcept { return this->m_Binds; };
    inline const std::string getNetworkMode() noexcept { return this->m_NetworkMode; };
    inline const std::string getRestartPolicy() noexcept { return this->m_RestartPolicy; };
    inline const std::string getHostname() noexcept { return this->m_Hostname; };

   private:
    std::string m_StartedAt;
    std::string m_FinishedAt;
    std::string m_Platform;
    std::string m_AppArmorProfile;
    std::string m_Binds;
    std::string m_NetworkMode;
    std::string m_RestartPolicy;
    std::string m_Hostname;
    std::string m_Mounts;
    std::string m_ConfigDomainname;
    std::string m_ConfigUser;
    std::string m_ConfigExposedPorts;
    std::string m_Cmd;
    std::string container_working_directory_string_;
    std::string m_Ipv4Address;
    bool m_Tty;
    bool m_OpenStdin;
};

struct TestStruct {
    TestStruct() { this->clear(); };

    void parse(const nlohmann::ordered_json &ordered_json_object) {
        this->clear();

        this->name = this->get_name_string_from_json_array(ordered_json_object, "Names");
        this->id = ordered_json_object.at("Id");
        this->image = ordered_json_object.at("Image");
        this->state = ordered_json_object.at("State");
        this->status = ordered_json_object.at("Status");
        this->command = ordered_json_object.at("Command");
        this->ports = ordered_json_object.at("Ports").dump();
    };

    void print_parsed() {
        fmt::print("Container name: {}\n", this->name);
        fmt::print(" - ID: {}\n", this->id);
        fmt::print(" - image_name: {}\n", this->image);
        fmt::print(" - Command: {}\n", this->command);
        fmt::print(" - state: {}\n", this->state);
        fmt::print(" - Status: {}\n", this->status);
        fmt::print(" - Ports: {}\n", this->ports);
    }

    void clear() {
        this->name.clear();
        this->id.clear();
        this->image.clear();
        this->command.clear();
        this->state.clear();
        this->status.clear();
        this->ports.clear();
    };

   private:
    inline std::string get_name_string_from_json_array(const nlohmann::ordered_json &jsonArrayObj,
                                                       const std::string &searchString) noexcept {
        std::string tmp = jsonArrayObj.at(searchString).dump();
        size_t pos1 = tmp.find('"');
        std::string name = tmp.substr(pos1 + 2);
        size_t pos2 = name.find('"');
        name = name.substr(0, pos2);
        return name;
    }

   private:
    std::string name{};
    std::string id{};
    std::string image{};
    std::string command{};
    std::string state{};
    std::string status{};
    std::string ports{};
};

}  // namespace Parser
}  // namespace DockerLib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_PARSER_CONTAINER_H
