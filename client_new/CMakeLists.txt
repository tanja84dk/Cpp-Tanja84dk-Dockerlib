cmake_minimum_required(VERSION 3.16)

project(tanja84dk_dockerclient_httplib LANGUAGES CXX)

include(cmake/CPM.cmake)

include(CheckCCompilerFlag)

set(tanja84dk_dockerclient_httplib_SOURCES
    src/main.cpp
)

set(tanja84dk_dockerclient_httplib_HEADERS)

set(tanja84dk_dockerclient_httplib_LIBRARIES)

CPMAddPackage(
    NAME            cpp-httplib
    GIT_REPOSITORY  https://github.com/yhirose/cpp-httplib
    VERSION         0.14.1
    GIT_TAG         v0.14.1
)

add_executable(tanja84dk_dockerclient_httplib ${tanja84dk_dockerclient_httplib_SOURCES})

target_link_directories(tanja84dk_dockerclient_httplib
    PRIVATE
        ${httplib_SOURCE_DIR}
)

target_link_libraries(tanja84dk_dockerclient_httplib
    PRIVATE
        Tanja84dk::dockerlib
        httplib
)

set_target_properties(tanja84dk_dockerclient_httplib
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        VERSION ${tanja84dk_dockerlib_VERSION}
)
