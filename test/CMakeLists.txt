cmake_minimum_required(VERSION 3.8)

project(tanja84dk_dockerlib_tests)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/CPM.cmake)

find_package(googletest REQUIRED)

add_executable(tanja84dk_dockerlib_tests "src/main_test.cpp")

set_target_properties(tanja84dk_dockerlib_tests
  PROPERTIES
    FOLDER Tests
)

target_link_libraries(tanja84dk_dockerlib_tests
  PRIVATE
    Tanja84dk::dockerlib
    gtest
)

add_test(tanja84dk_dockerlib_tests tanja84dk_dockerlib_tests)