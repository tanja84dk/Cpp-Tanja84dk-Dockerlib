cmake_minimum_required(VERSION 3.16)

project(tanja84dk_dockerlib VERSION 0.1.0)

include(CTest)
enable_testing()

set(POSITION_INDEPENDENT_CODE True)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(cmake/tanja84dk_warnings.cmake)

option(BUILD_SHARED_LIBS OFF)

option(tanja84dk_dockerlib_BUILD_CLIENT "Flag to build the test client" ON)
option(tanja84dk_dockerlib_BUILD_TEST "Set to ON to build tests" OFF)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CPM.cmake)

set(tanja84dk_dockerlib_HEADERS
  include/Tanja84dk/dockerlib/api/container.h
  include/Tanja84dk/dockerlib/api/datatype.h
  include/Tanja84dk/dockerlib/api/image.h
  include/Tanja84dk/dockerlib/api/network.h
  include/Tanja84dk/dockerlib/tanja84dk_dockerlib_pch.h
  include/Tanja84dk/dockerlib/docker_client.h
  include/Tanja84dk/dockerlib/dockerlib.h
  include/Tanja84dk/dockerlib/license.h
  include/Tanja84dk/dockerlib/settings.h
  include/Tanja84dk/dockerlib/web_requests.h
  include/Tanja84dk/dockerlib/api.h
  include/Tanja84dk/dockerlib/parser.h
  include/Tanja84dk/dockerlib/parser/container.h
  include/Tanja84dk/dockerlib/parser/image.h
)

set(tanja84dk_dockerlib_SOURCES
  src/api/datatype.cpp
  src/api/container.cpp
  src/api/image.cpp
  src/api/network.cpp
  src/parser/container.cpp
  src/docker_client.cpp
  src/license.cpp
  src/license_helper.h
)

set(tanja84dk_dockerlib_LIBRARIES
  fmt
  asio
  Tanja84dk::http
  nlohmann_json
)

find_package(Threads QUIET REQUIRED)
find_package(asio QUIET REQUIRED)
find_package(tanja84dk_http REQUIRED)
find_package(nlohmann_json QUIET REQUIRED)
find_package(fmt QUIET REQUIRED)

include(cmake/tanja84dk_generate_licenses.cmake)
tanja84dk_generate_license_begin()

if (tanja84dk_dockerlib_BUILD_CLIENT STREQUAL ON)
    find_package(cxxopts REQUIRED)
    tanja84dk_generate_license(cxxopts)
endif()

tanja84dk_generate_license_manual(tanja84dk_dockerlib ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
tanja84dk_generate_license_manual(asio ${asio_SOURCE_DIR}/asio/LICENSE_1_0.txt)
tanja84dk_generate_license_manual(fmt ${fmt_SOURCE_DIR}/LICENSE.rst)
tanja84dk_generate_license_manual(nlohmann_json ${nlohmann_json_SOURCE_DIR}/LICENSE.MIT)
tanja84dk_generate_license(tanja84dk_http)

tanja84dk_generate_license_end()

configure_file(${${PROJECT_NAME}_LICENSES_MACRO_FILE} include/Tanja84dk/dockerlib/${PROJECT_NAME}_licenses_macro.h)
configure_file(tanja84dk_dockerlib_config.h.in include/Tanja84dk/dockerlib/tanja84dk_dockerlib_config.h)

add_library(tanja84dk_dockerlib ${tanja84dk_dockerlib_SOURCES} ${tanja84dk_dockerlib_HEADERS})

add_library(Tanja84dk::dockerlib ALIAS tanja84dk_dockerlib)

target_link_libraries(tanja84dk_dockerlib ${tanja84dk_dockerlib_LIBRARIES})

target_include_directories(tanja84dk_dockerlib
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# PCH support
option(tanja84dk_dockerlib_BUILD_USING_PCH "Build using pre-compile header support" ON)
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.16 AND tanja84dk_dockerlib_BUILD_USING_PCH)
  message(STATUS "Compiling using pre-compiled header support")
  target_precompile_headers(tanja84dk_dockerlib PRIVATE include/Tanja84dk/dockerlib/tanja84dk_dockerlib_pch.h)
  set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
else()
  message(STATUS "Disabled pre-compiled header support")
endif()

target_compile_options(tanja84dk_dockerlib
  PRIVATE
    ${WERROR_FLAG}
    ${PEDANTIC_COMPILE_FLAGS}
)

target_compile_features(tanja84dk_dockerlib
  PRIVATE
    cxx_std_17
)

set_target_properties(tanja84dk_dockerlib
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VERSION ${tanja84dk_dockerlib_VERSION}
    SOVERSION ${tanja84dk_dockerlib_VERSION_MAJOR}
    FOLDER Libraries
)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR OR tanja84dk_dockerlib_BUILD_CLIENT STREQUAL ON )
  add_subdirectory(Client)
endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR OR tanja84dk_dockerlib_BUILD_TEST STREQUAL ON )
  enable_testing()
  add_subdirectory(test)
endif()

set(CPACK_PROJECT_NAME tanja84dk_dockerlib)
set(CPACK_PROJECT_VERSION ${tanja84dk_dockerlib_VERSION})
include(CPack)
