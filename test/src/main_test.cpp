#include <Tanja84dk/http/headers.h>

#include <catch2/catch_all.hpp>
#include <string>

TEST_CASE("Header Obj Test") {
    Tanja84dk::http::Headers HeaderClient;
    CHECK(HeaderClient.get_data_type() == "application/json");
    HeaderClient.set_host("google.com");
    CHECK(HeaderClient.get_host() == "google.com");
}
