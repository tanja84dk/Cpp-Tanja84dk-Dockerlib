CPMAddPackage(
    NAME cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts
    VERSION 3.1.1
    OPTIONS
        "BUILD_TESTING OFF"
        "CXXOPTS_BUILD_EXAMPLES OFF"
        #"CXXOPTS_USE_UNICODE_HELP ON"
)