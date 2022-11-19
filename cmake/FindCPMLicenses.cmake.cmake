CPMAddPackage(
    NAME CPMLicenses.cmake 
    GITHUB_REPOSITORY cpm-cmake/CPMLicenses.cmake
    VERSION 0.0.5
)

cpm_licenses_create_disclaimer_target(
    write-licenses "${CMAKE_CURRENT_BINARY_DIR}/third_party.txt" "${CPM_PACKAGES}"
)