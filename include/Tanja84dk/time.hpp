#ifndef TANJA84DK_TIME_HPP
#define TANJA84DK_TIME_HPP

#include <string>
#include <ctime>

namespace Tanja84dk::Time
{
    std::string unixTimeToHumanReadable(const int64_t &epochTime);
    std::string unixTimeToHumanReadable(const int64_t &epochTime, const char *tzFormat);
}

#endif // TANJA84DK_TIME_HPP