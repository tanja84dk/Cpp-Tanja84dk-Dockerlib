#include "client_tools.h"

using namespace Tanja84dk::DockerLib::Client;

nlohmann::ordered_json Tools::get_json(const char* data) noexcept {
    nlohmann::ordered_json output_json = {};
    output_json.clear();
    output_json = nlohmann::ordered_json::parse(data);
    return output_json;
}
