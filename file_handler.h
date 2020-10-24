#ifndef file_handler
#define file_handler

#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

namespace file_handler
{
    bool make_folders(string path)
    {
        bool check;
        for (char &c : path)
        {
            if (c == '\\')
            {
                c = '\0';
                check = (bool)(CreateDirectory(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS);
                if (!check)
                    return false;
                c = '\\';
            }
        }
        return true;
    }

    string get_full_path(const string &path = "D:\\project\\testing\\", const string &name = "test_file.txt")
    {
        if (path[path.length() - 1] == '\\')
            return path + name;
        else
            return path + '\\' + name;
    }

    bool initial(const string &path = "D:\\project\\testing\\", const string &name = "test_file.txt")
    {
        bool check = make_folders(path);
        if (!check)
            return false;

        fstream file(get_full_path(path, name), ios::app);
        if (!file)
            return false;
        file.close();
        return true;
    }

    bool write(const string &captured, const string full_path = get_full_path())
    {
        fstream file(full_path, ios::app);
        if (!file)
            return false;
        file << captured;
        file.close();
        return true;
    }

} // namespace file_handler

#endif