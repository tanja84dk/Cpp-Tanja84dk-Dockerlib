cmake_minimum_required(VERSION 3.14...3.16.6)

project(Tanja84dkDocker VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -Wconversion")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# -Wconversion

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING ON)
enable_testing()

#set(CMAKE_EXE_LINKER_FLAGS "-static")



list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CPM.cmake)

set(Headers
    include/Tanja84dk/DockerClient.h
)

set(Sources
    src/DockerClient.cpp
)

set(Libreries
    asio)

find_package(Threads REQUIRED)
find_package(asio REQUIRED)
find_package(curl)


add_library(${PROJECT_NAME} ${Sources} ${Headers})

add_library(Tanja84dk::Docker ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} asio)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    FOLDER Libraries
)

add_subdirectory(Client)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()