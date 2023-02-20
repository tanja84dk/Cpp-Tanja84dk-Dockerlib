#include <Tanja84dk/time.hpp>
#include <ctime>
namespace Tanja84dk::Time
{
    /// @brief
    /// @param epochTime
    /// @return
    std::string unixTimeToHumanReadable(const int64_t &epochTime)
    {
        return unixTimeToHumanReadable(epochTime, "%Y-%m-%d %H:%M:%S");
    };

    /// @brief
    /// @param epochTime
    /// @param tzFormat
    /// @return
    std::string unixTimeToHumanReadable(const int64_t &epochTime, const char *tzFormat)
    {
        time_t epochTimeBuffer = epochTime;
        struct tm *timeinfo = std::gmtime(&epochTimeBuffer);
        char timeBuffer[80];

        std::strftime(timeBuffer, 80, tzFormat, timeinfo);

        std::string timeHumanReadable(timeBuffer);

        return timeHumanReadable;
    }
}