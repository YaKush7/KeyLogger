#include <windows.h>
#include <winuser.h>
#include <bits/stdc++.h>

#include "key_hook.h"

using namespace std;

int main()
{
    bool check = key_hook::create_hook();
    if (check)
        cout << "\n\n\t\tHooked\n\n";
    else
        return 1;

    MessageBoxW(NULL, L"hooking", L"", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);

    check = key_hook::delete_hook();
    if (check)
        cout << "\n\n\t\tUnHooked\n\n";
    else
        return 2;

    return 0;
}
