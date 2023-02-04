#ifndef TANJA84DK_DOCKERLIB_PARSER_CONTAINER_HPP
#define TANJA84DK_DOCKERLIB_PARSER_CONTAINER_HPP

#include <string>
#include <fmt/core.h>
#include <nlohmann/json.hpp>

namespace Tanja84dk::DockerLib::Parser
{
    struct ContainersDataStore
    {
        friend struct ContainersInterface;
        virtual void parse([[maybe_unused]] const nlohmann::ordered_json &jsonOrdered) = 0;

    private:
        std::string m_Id;
        std::string m_Name;
        std::string m_State;
        std::string m_PortBindings;
        std::string m_Image;
        std::string m_WorkingDir;
        std::string m_Entrypoint;
    };

    struct ContainersInterface : ContainersDataStore
    {
        friend struct Inspect;
        virtual void parse([[maybe_unused]] const nlohmann::ordered_json &jsonOrdered) = 0;

        // Getters
        inline const std::string getId() noexcept { return this->m_Id; };
        inline const std::string getName() noexcept { return this->m_Name; };
        inline const std::string getState() noexcept { return this->m_State; };
        inline const std::string getPortBinds() noexcept { return this->m_PortBindings; };
        inline const std::string getImage() noexcept { return this->m_Image; };
        inline const std::string getWorkingDir() noexcept { return this->m_WorkingDir; };
        inline const std::string getEntrypoint() noexcept { return this->m_Entrypoint; };

    private:
        // Setters
        inline void setId(const std::string &Id) noexcept { this->m_Id = Id; };
        inline void setName(const std::string &Name) noexcept { this->m_Name = Name; };
        inline void setState(const std::string &State) noexcept { this->m_State = State; };
        inline void setPortBinds(const std::string &PortBindings) noexcept { this->m_PortBindings = PortBindings; };
        inline void setImage(const std::string &Image) noexcept { this->m_Image = Image; };
        inline void setWorkingDir(const std::string &WorkingDir) noexcept { this->m_WorkingDir = WorkingDir; };
        inline void setEntrypoint(const std::string &EntryPoint) noexcept { this->m_Entrypoint = EntryPoint; };
    };

    struct Inspect : ContainersInterface
    {

        void parse(const nlohmann::ordered_json &jsonOrdered) noexcept override
        {
            this->setId(jsonOrdered.at("Id"));
            this->setState(jsonOrdered.at("State").at("Status"));
            this->m_StartedAt = jsonOrdered.at("State").at("StartedAt");
            this->m_FinishedAt = jsonOrdered.at("State").at("FinishedAt");
            this->setName(jsonOrdered.at("Name"));
            this->m_Platform = jsonOrdered.at("Platform");
            this->m_AppArmorProfile = jsonOrdered.at("AppArmorProfile");
            this->m_Binds = jsonOrdered.at("HostConfig").at("Binds").dump();
            this->m_NetworkMode = jsonOrdered.at("HostConfig").at("NetworkMode");
            this->m_RestartPolicy = jsonOrdered.at("HostConfig").at("RestartPolicy").at("Name");
            this->m_Hostname = jsonOrdered.at("Config").at("Hostname");
            this->setImage(jsonOrdered.at("Config").at("Image"));
            this->setWorkingDir(jsonOrdered.at("Config").at("WorkingDir"));
            this->setEntrypoint(jsonOrdered.at("Config").at("Entrypoint").dump());
            this->m_Mounts = jsonOrdered.at("Mounts").dump();
            this->m_ConfigDomainname = jsonOrdered.at("Config").at("Domainname");
            this->m_ConfigUser = jsonOrdered.at("Config").at("User");
            this->m_ConfigExposedPorts = jsonOrdered.at("Config").at("ExposedPorts").dump();
            this->m_Tty = jsonOrdered.at("Config").at("Tty");
        };

        inline void printParsed() noexcept
        {
            fmt::print("Container Name: {}\n", this->getName());
            fmt::print(" - ID: {}\n", this->getId());
            fmt::print(" - State/Status: {}\n", this->getState());
            fmt::print(" - Started At: {}\n", this->m_StartedAt);
            fmt::print(" - Finished At: {}\n", this->m_FinishedAt);
            fmt::print(" - Platform: {}\n", this->m_Platform);
            fmt::print(" - AppArmor Profile: {}\n", this->m_AppArmorProfile);
            // fmt::print(" - Exec ID: {}\n", this->m_ExecId);
            fmt::print(" - Binds: {}\n", this->m_Binds);
            fmt::print(" - Network Mode: {}\n", this->m_NetworkMode);
            fmt::print(" - Port Bindings: {}\n", this->getPortBinds());
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
            fmt::print(" - Image: {}\n", this->getImage());
            fmt::print(" - Working Directory: {}\n", this->m_WorkingDir);
            fmt::print(" - Entrypoint: {}\n", this->getEntrypoint());
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
        bool m_Tty;
    };

    struct TestStruct
    {
        TestStruct() { this->clear(); };

        void parse(const nlohmann::ordered_json &jsonObj)
        {
            this->clear();

            this->m_name = this->getStringFromNameJSONArray(jsonObj, "Names");
            this->m_id = jsonObj.at("Id");
            this->m_image = jsonObj.at("Image");
            this->m_state = jsonObj.at("State");
            this->m_status = jsonObj.at("Status");
            this->m_command = jsonObj.at("Command");
            this->m_ports = jsonObj.at("Ports").dump();
        };

        void printParsed()
        {
            fmt::print("Container Name: {}\n", this->m_name);
            fmt::print(" - ID: {}\n", this->m_id);
            fmt::print(" - Image: {}\n", this->m_image);
            fmt::print(" - Command: {}\n", this->m_command);
            fmt::print(" - State: {}\n", this->m_state);
            fmt::print(" - Status: {}\n", this->m_status);
            fmt::print(" - Ports: {}\n", this->m_ports);
        }

        void clear()
        {
            this->m_name.clear();
            this->m_id.clear();
            this->m_image.clear();
            this->m_command.clear();
            this->m_state.clear();
            this->m_status.clear();
            this->m_ports.clear();
        };

    private:
        inline std::string getStringFromNameJSONArray(const nlohmann::ordered_json &jsonArrayObj, const std::string &searchString) noexcept
        {
            std::string tmp = jsonArrayObj.at(searchString).dump();
            size_t pos1 = tmp.find('"');
            std::string name = tmp.substr(pos1 + 2);
            size_t pos2 = name.find('"');
            name = name.substr(0, pos2);
            return name;
        }

    private:
        std::string m_name{};
        std::string m_id{};
        std::string m_image{};
        std::string m_command{};
        std::string m_state{};
        std::string m_status{};
        std::string m_ports{};
    };

}

#endif // TANJA84DK_DOCKERLIB_PARSER_CONTAINER_HPP