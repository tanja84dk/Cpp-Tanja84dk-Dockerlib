cmake_minimum_required(VERSION 3.8)
project(${CMAKE_PROJECT_NAME}_tests
    VERSION ${Tanja84dkDocker_VERSION}
    LANGUAGES CXX)

set(Sources
    src/main.cpp
)

set(Libraries
    Tanja84dk::Docker)

find_package(asio REQUIRED)
find_package(gflags REQUIRED)
find_package(glog REQUIRED)

add_executable(${PROJECT_NAME} ${Sources})
set_target_properties(${PROJECT_NAME} PROPERTIES
    FOLDER Tests
)

#target_include_directories(${This} PRIVATE ..)

target_link_libraries(${PROJECT_NAME} PRIVATE ${Libraries})

add_test(${PROJECT_NAME} ${PROJECT_NAME})
