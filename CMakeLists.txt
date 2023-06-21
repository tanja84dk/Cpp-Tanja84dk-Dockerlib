cmake_minimum_required(VERSION 3.16)

project(tanja84dk_dockerlib VERSION 0.1.0)

include(CTest)
enable_testing()

set(POSITION_INDEPENDENT_CODE True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include(CheckCXXCompilerFlag)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(PEDANTIC_COMPILE_FLAGS -pedantic-errors -Wall -Wextra -pedantic
      -Wold-style-cast -Wundef
      -Wredundant-decls -Wwrite-strings -Wpointer-arith
      -Wcast-qual -Wformat=2 -Wmissing-include-dirs
      -Wcast-align
      -Wctor-dtor-privacy -Wdisabled-optimization
      -Winvalid-pch -Woverloaded-virtual
      -Wconversion -Wundef
      -Wno-ctor-dtor-privacy -Wno-format-nonliteral)
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}
         -Wno-dangling-else -Wno-unused-local-typedefs)
  endif ()
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wdouble-promotion
          -Wtrampolines -Wzero-as-null-pointer-constant -Wuseless-cast
          -Wvector-operation-performance -Wsized-deallocation -Wshadow)
  endif ()
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wshift-overflow=2
          -Wnull-dereference -Wduplicated-cond)
  endif ()
  set(WERROR_FLAG -Werror)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(PEDANTIC_COMPILE_FLAGS -Wall -Wextra -pedantic -Wconversion -Wundef
    -Wdeprecated -Wweak-vtables -Wshadow
    -Wno-gnu-zero-variadic-macro-arguments)
  check_cxx_compiler_flag(-Wzero-as-null-pointer-constant HAS_NULLPTR_WARNING)
  if (HAS_NULLPTR_WARNING)
    set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}-Wzero-as-null-pointer-constant)
  endif ()
  set(WERROR_FLAG -Werror)
endif ()

if (MSVC)
  set(PEDANTIC_COMPILE_FLAGS /W4)
  set(WERROR_FLAG /WX)
endif ()

option(BUILD_SHARED_LIBS OFF)

option(tanja84dk_dockerlib_BUILD_CLIENT "Flag to build the test client" ON)
option(tanja84dk_dockerlib_BUILD_TEST "Set to ON to build tests" OFF)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CPM.cmake)

set(tanja84dk_dockerlib_HEADERS
  include/Tanja84dk/dockerlib/tanja84dk_dockerlib_pch.h
  include/Tanja84dk/dockerlib/docker_client.h
  include/Tanja84dk/dockerlib/dockerlib.h
  include/Tanja84dk/dockerlib/settings.h
  include/Tanja84dk/dockerlib/web_requests.h
  include/Tanja84dk/dockerlib/api.h
)

set(tanja84dk_dockerlib_SOURCES
  src/docker_client.cpp
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
        ${PEDANTIC_COMPILE_FLAGS})

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

#if( Tanja84dkDocker_BUILD_TESTS )
#    enable_testing()
#    add_subdirectory(test)
#endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR OR tanja84dk_dockerlib_BUILD_TEST STREQUAL ON )
  enable_testing()
  add_subdirectory(test)
endif()

set(CPACK_PROJECT_NAME tanja84dk_dockerlib)
set(CPACK_PROJECT_VERSION ${tanja84dk_dockerlib_VERSION})
include(CPack)
