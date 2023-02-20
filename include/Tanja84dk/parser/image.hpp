#ifndef TANJA84DK_DOCKERLIB_PARSER_IMAGE_HPP
#define TANJA84DK_DOCKERLIB_PARSER_IMAGE_HPP

#include <string>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <Tanja84dk/time.hpp>

namespace Tanja84dk::DockerLib::Parser::Image
{
    struct ImageDataStore
    {
        friend struct ImageInterface;

    private:
        std::string m_Id;
        std::string m_ParentId;
        std::string m_Created;
        std::string m_Name;
        std::string m_Image;
        std::string m_RepoTags;
        size_t m_Size{};
        size_t m_VirtualSize{};
    };

    struct ImageInterface : ImageDataStore
    {
        friend struct Inspect;

        virtual void parse([[maybe_unused]] const nlohmann::ordered_json &jsonOrdered) = 0;
        virtual void printParsed() = 0;

        /// @brief Getting the stored ID from parsing
        /// @return Return's std::string
        inline const std::string getId() noexcept { return this->m_Id; };
        /// @brief Getting the Created Date and timestamp from parsing
        /// @return Return's std::string
        inline const std::string getCreated() noexcept { return this->m_Created; };

    private:
        inline void setId(const std::string &Id) noexcept { this->m_Id = Id; };
        inline void setParentId(const std::string &ParentId) noexcept { this->m_ParentId = ParentId; };
        inline void setCreated(const std::string &TimeHumanReadable) noexcept { this->m_Created = TimeHumanReadable; };
        inline void setName(const std::string &Name) noexcept { this->m_Name = Name; };
        inline void setImage(const std::string &Image) noexcept { this->m_Image = Image; };
        inline void setRepoTags(const std::string &RepoTags) noexcept { this->m_RepoTags = RepoTags; };
        inline void setSize(const size_t &Size) noexcept { this->m_Size = Size; };
        inline void setVirtualSize(const size_t &VirtualSize) noexcept { this->m_VirtualSize = VirtualSize; };
    };

    struct Inspect : ImageInterface
    {

        /// @brief Parsing a docker API response
        /// @param jsonOrdered json object as a reference
        void parse(const nlohmann::ordered_json &jsonOrdered) noexcept override
        {
            this->setId(jsonOrdered.at("Id"));
            this->setCreated(Tanja84dk::Time::unixTimeToHumanReadable(stoll(jsonOrdered.at("Created").dump())));
        };
        /// @brief Printing the Parsed object
        inline void printParsed() noexcept override
        {
            fmt::print(" - ID: {}\n", this->getId());
            fmt::print(" - Created: {}\n", this->getCreated());
        }
    };

}
#endif // TANJA84DK_DOCKERLIB_PARSER_IMAGE_HPP