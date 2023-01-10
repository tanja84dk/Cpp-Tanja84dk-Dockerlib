# Cpp-Tanja84dk-Dockerlib

## 1. Introduction

![Screenshot](/screenshot/img01.png?raw=true){ width=50% }

### 1.1 Background

I had several times needed a small docker client to check if containers were running in a remote server, and often I actually did'nt need the complete docker install or if on linux then the full docker-cli package

### 1.2 Working at this moment

The things there is working at this point in tome is that you are able to list all containers, and also start, stop, restart and kill containers

I do have to add a note that at this point its only omunicating over HTTP ( So no SSL )

## 2. Technical

### 2.1 Required libraries

 - CPM - CMake dependency management 0.36.0
 - asio 1.24.0
 - fmt 9.1.0
 - nlohmann_json 3.11.2
 - cxxopts 3.0.0

### 2.2 Requiring libraries

CMake dependency management is used to download the required libraries for compiling so its not needed for you to have it installed on your system prior compiling

By default its downloading the libraries to the build folder and is storing them within a folder called _deps

About asio that is used as INTERFACE library and with ASIO_STANDALONE enabled so boost arent required

## 3. Licenses

 - Cpp-Tanja84dk-Dockerlib ( This project ) is licensed under MIT [Cpp-Tanja84dk-Dockerlib License](LICENSE)
 - CPM is licensed under MIT [CPM 0.36.0 License](https://github.com/cpm-cmake/CPM.cmake/blob/v0.36.0/LICENSE)
 - asio is licensed under Boost Software License - Version 1.0 [asio License](https://github.com/chriskohlhoff/asio/blob/asio-1-24-0/asio/LICENSE_1_0.txt)
 - fmt is licensed under MIT [fmt 9.1.0 License](https://github.com/fmtlib/fmt/blob/9.1.0/LICENSE.rst)
 - nlohmann_json is licensed under MIT [nlohmann_json 3.11.2 License](https://github.com/nlohmann/json/blob/v3.11.2/LICENSE.MIT)
 - cxxopts in licensed under MIT [cxxopts 3.0.0 License](https://github.com/jarro2783/cxxopts/blob/v3.0.0/LICENSE)

## 4. Credit

 - CPM for the depentencies manager [Github](https://github.com/cpm-cmake/CPM.cmake)
 - Asio C++ Library for the networking library [Github](https://github.com/chriskohlhoff/asio/) [Website](http://think-async.com/Asio/)
 - fmt for the formatting library [Github](https://github.com/fmtlib/fmt) [Website](https://fmt.dev/)
 - nlohmann_json for the json library [Github](https://github.com/nlohmann/json) [Website](https://json.nlohmann.me/)
 - cxxopts for the option parser library GNU style [Github](https://github.com/jarro2783/cxxopts)
