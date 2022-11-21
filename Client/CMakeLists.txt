cmake_minimum_required(VERSION 3.16)
project(${CMAKE_PROJECT_NAME}Client
    VERSION ${Tanja84dkDocker_VERSION}
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)

set(Sources
    src/main.cpp
)

set(Libraries
    fmt
    Tanja84dk::Docker
    nlohmann_json
    cxxopts
)

find_package(cxxopts REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} ${Sources})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    FOLDER
        Application
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${Libraries})
