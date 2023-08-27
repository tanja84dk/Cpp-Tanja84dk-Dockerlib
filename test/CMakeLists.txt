find_package(Catch2 3 REQUIRED)

add_executable(tanja84dk_dockerlib_tests src/main_test.cpp)
target_link_libraries(tanja84dk_dockerlib_tests
    PRIVATE
        Tanja84dk::dockerlib
        Catch2::Catch2WithMain
)

set_target_properties(tanja84dk_dockerlib_tests
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        CMAKE_FOLDER Testing
)
