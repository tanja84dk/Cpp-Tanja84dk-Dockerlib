cmake_minimum_required(VERSION 3.8)

project(tanja84dk_dockerlib_tests)

add_executable(tanja84dk_dockerlib_tests "src/main_test.cpp")

set_target_properties(tanja84dk_dockerlib_tests
  PROPERTIES
    FOLDER Tests
)

target_link_libraries(tanja84dk_dockerlib_tests
  PRIVATE
    Tanja84dk::dockerlib
)

add_test(tanja84dk_dockerlib_tests tanja84dk_dockerlib_tests)