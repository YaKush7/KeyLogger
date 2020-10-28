#ifndef DATE_TIME
#define DATE_TIME

#include <chrono>
#include <sstream>
#include <iomanip>
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

    string get_date_time(const string &s1 = "/", const string &s2 = ":")
    {
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        string s = "%Y" + s1 + "%m" + s1 + "%d  %I" + s2 + "%M" + s2 + "%S %p";
        stringstream ss;
        ss << std::put_time(std::localtime(&now), s.c_str());
        return ss.str();
    }

} // namespace date_time

#endif
