#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <string>
#include <windows.h>
#include <fstream>

#include "date_time.h"

using namespace std;

namespace file_handler
{
    const string path = "D:\\project\\testing\\";
    const string name = "test_file.txt";

    void write_logs(const string &msg)
    {
        fstream file(path + "logs.log", ios::app);
        if (!file)
            return;

        file << "<<" << date_time::get_date_time() << ">>  " << msg << "\n";
        file.close();
    }

    bool make_folders(string file_path)
    {
        bool check;
        for (char &c : file_path)
        {
            if (c == '\\')
            {
                c = '\0';
                check = (bool)(CreateDirectoryA(file_path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS);
                if (!check)
                    return false;
                c = '\\';
            }
        }
        return true;
    }

    string get_full_path()
    {
        if (path[path.length() - 1] == '\\')
            return path + name;
        else
            return path + '\\' + name;
    }

    bool initial()
    {
        bool check = make_folders(path);
        if (!check)
        {
            write_logs("Can't create folders --> " + path);
            return false;
        }

        fstream file(get_full_path(), ios::app);
        if (!file)
        {
            write_logs("Can't create/open intercept file --> " + get_full_path());
            return false;
        }

        file.close();
        write_logs("Successfully created file/folders");
        return true;
    }

    bool write_intercept(const string &captured)
    {
        if (captured.length() == 0)
            return true;

        const string full_path = get_full_path();
        fstream file(full_path, ios::app);
        if (!file)
        {
            write_logs("Can't create/open intercept file --> " + get_full_path());
            return false;
        }
        file << "<<" << date_time::get_date_time() << ">>\n"
             << captured << "\n";
             
        file.close();
        write_logs("Successfully wrote intercept");
        return true;
    }

} // namespace file_handler

#endif