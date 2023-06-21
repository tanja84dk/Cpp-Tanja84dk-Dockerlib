CPMAddPackage(
    NAME              googletest
    GITHUB_REPOSITORY https://github.com/google/googletest
    GIT_TAG           release-1.13.0
    VERSION           1.13.0
    OPTIONS
      "INSTALL_GTEST OFF"
      "gtest_force_shared_crt"
)