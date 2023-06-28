CPMAddPackage(
  NAME            glog
  GIT_REPOSITORY  https://github.com/google/glog
  VERSION         0.7.0
  GIT_TAG         3a0d4d22c5ae0b9a2216988411cfa6bf860cc372
  OPTIONS
    "WITH_GFLAGS OFF"
    "BUILD_TESTING OFF"
)