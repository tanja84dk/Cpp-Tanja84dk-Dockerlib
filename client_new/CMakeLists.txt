cmake_minimum_required(VERSION 3.16)

project(tanja84dk_dockerclient_httplib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_STANDARD_REQUIRED 20)

include(cmake/CPM.cmake)

include(CheckCCompilerFlag)

set(tanja84dk_dockerclient_httplib_SOURCES
    src/main.cpp
    src/container.cpp
    src/client_parsing.cpp
    src/client_tools.cpp
    src/license.cpp
    src/license.h
    src/menu.h
    src/network.cpp
    src/network.h
    src/tanja84dk_dockerclient_httplib_licenses_macro.h
)

set(tanja84dk_dockerclient_httplib_LIBRARIES)

CPMAddPackage(
    NAME            fmt
    GIT_REPOSITORY  https://github.com/fmtlib/fmt
    VERSION         10.1.1
    GIT_TAG         10.1.1
)

CPMAddPackage(
    NAME            cpp-httplib
    GIT_REPOSITORY  https://github.com/yhirose/cpp-httplib
    VERSION         0.15.3
    GIT_TAG         v0.15.3
)

include(cmake/tanja84dk_generate_licenses.cmake)
tanja84dk_generate_license_begin()

#if (tanja84dk_dockerlib_BUILD_CLIENT STREQUAL ON)
#    find_package(cxxopts REQUIRED)
#    tanja84dk_generate_license(cxxopts)
#endif()

tanja84dk_generate_license_manual(tanja84dk_dockerlib ${CMAKE_SOURCE_DIR}/LICENSE)
#tanja84dk_generate_license_manual(asio ${asio_SOURCE_DIR}/asio/LICENSE_1_0.txt)
tanja84dk_generate_license_manual(fmt ${fmt_SOURCE_DIR}/LICENSE)
tanja84dk_generate_license_manual(nlohmann_json ${nlohmann_json_SOURCE_DIR}/LICENSE.MIT)
tanja84dk_generate_license_manual(cpp_httplib ${cpp-httplib_SOURCE_DIR}/LICENSE)
#tanja84dk_generate_license(tanja84dk_http)

tanja84dk_generate_license_end()

configure_file(${${PROJECT_NAME}_LICENSES_MACRO_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}_licenses_macro.h)

add_executable(tanja84dk_dockerclient_httplib ${tanja84dk_dockerclient_httplib_SOURCES})

target_link_directories(tanja84dk_dockerclient_httplib
    PRIVATE
        ${httplib_SOURCE_DIR}
)

target_compile_features(tanja84dk_dockerclient_httplib
    PRIVATE
        cxx_std_17
)

target_link_libraries(tanja84dk_dockerclient_httplib
    PRIVATE
        Tanja84dk::dockerlib
        fmt
        httplib
)

set_target_properties(tanja84dk_dockerclient_httplib
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        VERSION ${tanja84dk_dockerlib_VERSION}
)
