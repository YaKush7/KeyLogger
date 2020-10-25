#ifndef date_time
#define date_time

#include <chrono>
#include <sstream>
using namespace std;

namespace date_time
{
    string get_time()
    {
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        stringstream ss;
        ss << std::put_time(std::localtime(&now), "%I-%M-%S-%p");
        return ss.str();
    }

    string get_date()
    {
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        stringstream ss;
        ss << std::put_time(std::localtime(&now), "%Y-%m-%d");
        return ss.str();
    }

    string get_date_time()
    {
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        stringstream ss;
        ss << std::put_time(std::localtime(&now), "%Y/%m/%d  %I:%M:%S %p");
        return ss.str();
    }

} // namespace date_time

#endif