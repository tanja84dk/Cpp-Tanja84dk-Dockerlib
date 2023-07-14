#include <Tanja84dk/dockerlib/api/datatype.h>

using namespace Tanja84dk::dockerlib;

void api::ApiRequest::clear_all() noexcept {
    this->request_type.clear();
    this->data.clear();
    this->content_type.clear();
    this->url_path.clear();
    this->options.clear();
}
