#ifndef TANJA84DK_DOCKERLIB_CLIENT_CONTAINER_H
#define TANJA84DK_DOCKERLIB_CLIENT_CONTAINER_H

#include <string>

namespace Tanja84dk {
namespace client {
namespace container {

enum REQUEST_TYPE {
    GET = 1,
    POST = 2,
    DELETE = 3,
    HEAD = 4,
    PUT = 5,
};

/*
    application/json = 1,
    application/octet-stream = 2,
    text/plain = 3,
    application/vnd.docker.multiplexed-stream
    application/vnd.docker.raw-stream
*/
}  // namespace container
}  // namespace client
}  // namespace Tanja84dk

#endif  // TANJA84DK_DOCKERLIB_CLIENT_CONTAINER_H
