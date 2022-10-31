cmake_minimum_required(VERSION 3.8)
project(${CMAKE_PROJECT_NAME}Client
    VERSION ${Tanja84dkDocker_VERSION}
    LANGUAGES CXX)

set(Sources
    src/main.cpp
)

set(Libraries
    nlohmann_json
    Tanja84dk::Docker)

#find_package(asio REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} ${Sources})
#set_target_properties(${PROJECT_NAME} PROPERTIES
#)

#target_include_directories(${This} PRIVATE ..)

target_link_libraries(${PROJECT_NAME} PRIVATE ${Libraries})
