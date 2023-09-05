#include "Tanja84dk/dockerlib/parser/network.h"

using namespace Tanja84dk::dockerlib::parser;

namespace {
class Network_Datastore {
   public:
   protected:
    std::string name_ = {};
    std::string id_string_ = {};
    std::string scope_ = {};
    std::string driver_ = {};
    bool enable_ipv6_bool_ = {};
};

}  // namespace
