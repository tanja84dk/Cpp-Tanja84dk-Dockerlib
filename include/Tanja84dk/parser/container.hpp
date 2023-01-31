#ifndef TANJA84DK_DOCKERLIB_PARSER_CONTAINER_HPP
#define TANJA84DK_DOCKERLIB_PARSER_CONTAINER_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace Tanja84dk::DockerLib::Parser
{
    struct ContainersDataStore
    {
        friend struct ContainersInterface;

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
        virtual void parse([[maybe_unused]] const nlohmann::ordered_json &jsonOrdered){};

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
        };

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
    };

}

#endif // TANJA84DK_DOCKERLIB_PARSER_CONTAINER_HPP