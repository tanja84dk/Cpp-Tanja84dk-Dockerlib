#ifndef TANJA84DK_DOCKERLIB_PARSER_CONTAINER_H
#define TANJA84DK_DOCKERLIB_PARSER_CONTAINER_H

#include <nlohmann/json.hpp>
#include <string>

namespace Tanja84dk {
namespace dockerlib {
namespace parser {

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
    void parse(const nlohmann::ordered_json &ordered_json_object) noexcept override;

    inline void print_parsed() noexcept override;

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

    void parse(const nlohmann::ordered_json &ordered_json_object) noexcept;

    void print_parsed() noexcept;

    void clear() noexcept;

   private:
    inline std::string get_name_string_from_json_array(const nlohmann::ordered_json &json_array_object,
                                                       const std::string &search_string) noexcept {
        std::string tmp = json_array_object.at(search_string).dump();
        size_t pos1 = tmp.find('"');
        std::string name_string = tmp.substr(pos1 + 2);
        size_t pos2 = name_string.find('"');
        name_string = name_string.substr(0, pos2);
        return name_string;
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

}  // namespace parser
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_PARSER_CONTAINER_H
