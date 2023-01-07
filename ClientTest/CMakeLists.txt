cmake_minimum_required(VERSION 3.16)

project(ClientTest VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED 17)
set(CXX_EXTENSIONS OFF)

set(SOURCES
    src/main.cpp)

set(Libraries
    fmt
    Tanja84dk::Docker
    nlohmann_json
    cxxopts
)

find_package(cxxopts REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${Libraries})