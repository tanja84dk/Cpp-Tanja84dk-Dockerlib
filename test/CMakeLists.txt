find_package(googletest REQUIRED)

set(Sources
    src/main.cpp)

set(Libraries
    Tanja84dk::Docker
    gtest
    gtest_main
)


# Since Check uses Threads to paralelize the tests, it's mandatory
# add pthread as a dependency, alongside the Check libraries.
add_executable(test_sample ${Sources})
target_link_libraries(test_sample ${Libraries} pthread)

# Create testing target and redirect its output to `Testing` folder
add_test(NAME test_sample COMMAND test_sample WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(test_sample PROPERTIES TIMEOUT 30) 
