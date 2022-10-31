CPMAddPackage(
    NAME glog
    GIT_REPOSITORY https://github.com/google/glog
    VERSION 0.6.0
    OPTIONS
    "WITH_GFLAGS OFF"
    "BUILD_TESTING OFF"
)