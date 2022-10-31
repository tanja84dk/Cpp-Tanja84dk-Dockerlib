//
// sync_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <cstring>
#include <asio.hpp>
#include <nlohmann/json.hpp>
#include <sstream>

void printJsonPretty(int tabs, const nlohmann::ordered_json &obj)
{
    std::cout << std::setw(tabs) << obj;
    return;
}

using asio::ip::tcp;

int main(int argc, char *argv[])
{
    bool inputflag = false;
    char *PROGRAMNAME = argv[0] + '\0';
    char *HOST = nullptr;
    char *PORT = nullptr;
    char *PATH = nullptr;

    if (argc <= 1)
    {
        std::string manualHost = "";
        std::string manualPort = "";
        std::string manualPath = "";
        printf("Enter the server address: ");
        std::cin >> manualHost;
        printf("Enter the server port: ");
        std::cin >> manualPort;
        printf("Enter the path: ");
        std::cin >> manualPath;

        HOST = manualHost.data() + '\0';
        PORT = manualPort.data() + '\0';
        PATH = manualPath.data() + '\0';
        inputflag = true;
    }
    else
    {
        if (argc != 4 || inputflag == true)
        {
            std::cout << "Usage: " << PROGRAMNAME << " <server> <portnumber> <path>\n";
            std::cout << "Example:\n";
            std::cout << "  " << PROGRAMNAME << " www.boost.org portnumber /LICENSE_1_0.txt\n";
            return 1;
        }

        HOST = argv[1] + '\0';
        PORT = argv[2] + '\0';
        PATH = argv[3] + '\0';
    }

    try
    {
        asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(HOST, PORT);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        tcp::socket socket(io_service);
        asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET " << PATH << " HTTP/1.0\r\n";
        request_stream << "Host: " << HOST << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Send the request.
        asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        asio::streambuf response;
        asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cout << "Invalid response\n";
            return 1;
        }
        if (status_code != 200)
        {
            std::cout << "Response returned with status code " << status_code << "\n";
            return 1;
        }

        // Read the response headers, which are terminated by a blank line.
        asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
            std::cout << header << "\n";
        std::cout << "\n";

        // Write whatever content we already have to output.
        std::stringstream webdata;
        webdata.clear();
        if (response.size() > 0)
            webdata << &response;

        // std::cout << webdata.str();
        // nlohmann::json j_complete = nlohmann::json::parse(webdata);
        // std::cout << std::setw(4) << j_complete << "\n\n";

        // Read until EOF, writing data to output as we go.
        asio::error_code error;
        while (asio::read(socket, response,
                          asio::transfer_at_least(1), error))
            webdata << &response;
        if (error != asio::error::eof)
            std::cerr << "[ERROR]: ..\n";

        nlohmann::ordered_json j_complete = nlohmann::ordered_json::parse(webdata);
        printJsonPretty(4, j_complete);
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}