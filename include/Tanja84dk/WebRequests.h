#ifndef TANJA84DK_DOCKERLIB_WEBREQUESTS_H
#define TANJA84DK_DOCKERLIB_WEBREQUESTS_H

#include "Tanja84dkDocker_pch.h"
#include "Settings.h"

namespace Tanja84dk
{
    namespace Dockerlib
    {

        void httpGetRequest(asio::streambuf &request, const char *HOST, const char *PATH)
        {
            std::ostream request_stream(&request);
            request_stream << "GET " << PATH << " HTTP/1.1\r\n";
            request_stream << "User-Agent: Tanja84dkDocker/" << Tanja84dk::Dockerlib::versionAsString() << "\r\n";
            request_stream << "Host: " << HOST << "\r\n";
            request_stream << "Accept: application/json\r\n";
            request_stream << "Accept-Language: en-US, en;q=0.8, *;q=0.5\r\n";
            request_stream << "Connection: close\r\n\r\n";
        }

        void httpPostRequest(asio::streambuf &request, const char *HOST, const char *PATH, const std::string data = "")
        {
            std::ostream request_stream(&request);
            request_stream << "POST " << PATH << " HTTP/1.1\r\n";
            request_stream << "User-Agent: Tanja84dkDockerClient/" << Tanja84dk::Dockerlib::versionAsString() << "\r\n";
            request_stream << "Host: " << HOST << "\r\n";
            if (data.length() > 0)
            {
                request_stream << "Content-Length: " << data.length() << "\r\n";
            }
            else
            {
                request_stream << "Content-Length: 0\r\n";
            }
            request_stream << "Accept: application/json\r\n";
            request_stream << "Accept-Language: en-US, en;q=0.8, *;q=0.5\r\n";
            request_stream << "Connection: close\r\n\r\n";
            if (data.length() > 0)
            {
                request_stream << data;
            }
        }

        void httpDeleteRequest(asio::streambuf &request, const char *HOST, const char *PATH, const std::string data = "")
        {
            std::ostream request_stream(&request);
            request_stream << "DELETE " << PATH << " HTTP/1.1\r\n";
            request_stream << "User-Agent: Tanja84dkDockerClient/" << Tanja84dk::Dockerlib::versionAsString() << "\r\n";
            request_stream << "Host: " << HOST << "\r\n";
            if (data.length() > 0)
            {
                request_stream << "Content-Length: " << data.length() << "\r\n";
            }
            else
            {
                request_stream << "Content-Length: 0\r\n";
            }
            request_stream << "Accept: application/json\r\n";
            request_stream << "Accept-Language: en-US, en;q=0.8, *;q=0.5\r\n";
            request_stream << "Connection: close\r\n\r\n";
            if (data.length() > 0)
            {
                request_stream << data;
            }
        }

        void httpHeadRequest(asio::streambuf &request, const char *HOST, const char *PATH)
        {
            std::ostream request_stream(&request);
            request_stream << "HEAD " << PATH << " HTTP/1.1\r\n";
            request_stream << "User-Agent: Tanja84dkDocker/" << Tanja84dk::Dockerlib::versionAsString() << "\r\n";
            request_stream << "Host: " << HOST << "\r\n";
            request_stream << "Accept: application/json\r\n";
            request_stream << "Accept-Language: en-US, en;q=0.8, *;q=0.5\r\n";
            request_stream << "Connection: close\r\n\r\n";
        }

        void httpPutRequest(asio::streambuf &request, const char *HOST, const char *PATH, const std::string data = "")
        {
            std::ostream request_stream(&request);
            request_stream << "PUT " << PATH << " HTTP/1.1\r\n";
            request_stream << "User-Agent: Tanja84dkDockerClient/" << Tanja84dk::Dockerlib::versionAsString() << "\r\n";
            request_stream << "Host: " << HOST << "\r\n";
            if (data.length() > 0)
            {
                request_stream << "Content-Length: " << data.length() << "\r\n";
            }
            else
            {
                request_stream << "Content-Length: 0\r\n";
            }
            request_stream << "Accept: application/json\r\n";
            request_stream << "Accept-Language: en-US, en;q=0.8, *;q=0.5\r\n";
            request_stream << "Connection: close\r\n\r\n";
            if (data.length() > 0)
            {
                request_stream << data;
            }
        }
    } // namespace Dockerlib

} // namespace Tanja84dk

#endif // TANJA84DK_DOCKERLIB_WEBREQUESTS_H
