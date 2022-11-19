cmake_minimum_required(VERSION 3.16)
project(${CMAKE_PROJECT_NAME}Client
    VERSION ${Tanja84dkDocker_VERSION}
    LANGUAGES CXX)

include(cmake/CPM.cmake)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

set(CPACK_DEBIAN_PACKAGE_NAME "${PROJECT_NAME}")

set(CPACK_DEBIAN_PACKAGE_VERSION ${Tanja84dkDocker_VERSION})
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "some short description")

set(CPACK_PACKAGE_DESCRIPTION
"some very long long
long long description")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tanja84dk <tanja84dk@gmail.com>")

set(Sources
    src/main.cpp
)

set(Libraries
    fmt
    Tanja84dk::Docker
    nlohmann_json
)

find_package(cxxopts QUIET REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json)

add_executable(${PROJECT_NAME} ${Sources})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VERSION ${PROJECT_VERSION}
    FOLDER Application
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${Libraries})

include(CPack)
