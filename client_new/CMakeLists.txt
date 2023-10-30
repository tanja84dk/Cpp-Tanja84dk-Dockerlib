cmake_minimum_required(VERSION 3.16)

project(tanja84dk_dockerclient_httplib LANGUAGES CXX)

include(cmake/CPM.cmake)

include(CheckCCompilerFlag)

set(tanja84dk_dockerclient_httplib_SOURCES
    src/main.cpp
)

set(tanja84dk_dockerclient_httplib_HEADERS)

set(tanja84dk_dockerclient_httplib_LIBRARIES)

add_executable(tanja84dk_dockerclient_httplib ${tanja84dk_dockerclient_httplib_SOURCES})

set_target_properties(tanja84dk_dockerclient_httplib
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        VERSION ${tanja84dk_dockerlib_VERSION}
)
