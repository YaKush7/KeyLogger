#include <windows.h>
#include <winuser.h>
#include <future>

#include "key_hook.h"
#include "file_handler.h"
#include "thread_handler.h"

using namespace std;

int main()
{
    bool check = file_handler::initial();
    if (!check)
        return 0;

    check = key_hook::create_hook();
    if (!check)
        return 0;

    thread_handler::run = true;
    future<void> th = async(launch::async, thread_handler::timer, 10);

    MessageBoxW(NULL, L"\tHooking\t", L"Close to close XD", MB_ICONEXCLAMATION | MB_SYSTEMMODAL);

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

    thread_handler::run = false;
    th.get();

    check = key_hook::delete_hook();
    if (!check)
        return 0;

    return 0;
}
