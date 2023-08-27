#ifndef TANJA84DK_DOCKERLIB_PARSER_IMAGE_H
#define TANJA84DK_DOCKERLIB_PARSER_IMAGE_H

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Tanja84dk {
namespace dockerlib {
namespace parser {
class Image_Datastore {
   public:
   protected:
    std::string id_ = {};
    std::vector<std::string> repo_tags_ = {};
    std::string created_timestamp_ = {};
    std::vector<std::pair<std::string, std::string>> label_ = {};
};

class Image_Interface : Image_Datastore {
    inline const std::string &get_id() const noexcept { return this->id_; };
    inline const std::vector<std::string> &get_repo_tags() const noexcept { return this->repo_tags_; }
    inline const std::string &get_created_time_stamp() const noexcept { return this->created_timestamp_; };
    inline const std::vector<std::pair<std::string, std::string>> &get_labels() const noexcept { return this->label_; }

   private:
    inline void set_id_(const std::string &id_string) noexcept { this->id_ = id_string; }
    inline void set_repo_tags_([[maybe_unused]] const std::string &repo_tag_string) noexcept {
        [[maybe_unused]] std::string tags_buffer = {};
        std::vector<std::string> buffer_vector = {};
        buffer_vector.clear();
    }
};
}  // namespace parser
}  // namespace dockerlib
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_PARSER_IMAGE_H
