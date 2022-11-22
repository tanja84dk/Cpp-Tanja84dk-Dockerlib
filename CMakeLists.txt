cmake_minimum_required(VERSION 3.16)

project(Tanja84dkDocker VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(POSITION_INDEPENDENT_CODE True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra")
# Removed -Wconversion thanks to google
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)
#enable_testing()

#set(CMAKE_EXE_LINKER_FLAGS "-static")



list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CPM.cmake)

set(Headers
    include/Tanja84dk/Tanja84dkDocker_pch.h
    include/Tanja84dk/DockerClient.h
    include/Tanja84dk/DockerLib.h
    include/Tanja84dk/Settings.h
    include/Tanja84dk/WebRequests.h
)

set(Sources
    src/DockerClient.cpp
)

set(Libraries
    fmt
    asio
    nlohmann_json
    )

find_package(CPMLicenses.cmake REQUIRED)
find_package(Threads REQUIRED)
find_package(asio REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(fmt REQUIRED)

configure_file(${PROJECT_NAME}Config.h.in Configs/${PROJECT_NAME}Config.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/Configs)

add_library(${PROJECT_NAME} ${Sources} ${Headers})

add_library(Tanja84dk::Docker ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${Libraries})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# PCH support
option(${PROJECT_NAME}_BUILD_USING_PCH "Build using pre-compile header support" ON)
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.16 AND ${PROJECT_NAME}_BUILD_USING_PCH)
    message(STATUS "Compiling using pre-compiled header support")
    target_precompile_headers(${PROJECT_NAME} PRIVATE include/Tanja84dk/${PROJECT_NAME}_pch.h)
    set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
else()
    message(STATUS "Disabled pre-compiled header support")
endif()

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