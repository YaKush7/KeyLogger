#ifndef key_hook
#define key_hook

#include <windows.h>
#include "key_proc.h"

namespace key_hook
{
    HHOOK hhook = NULL;

    bool create_hook()
    {
        hhook = SetWindowsHookExW(WH_KEYBOARD_LL, key_proc::kbdproc, NULL, 0);
        if (hhook == NULL)
            return false;
        return true;
    }

    bool delete_hook()
    {
        BOOL check = UnhookWindowsHookEx(hhook);
        if ((bool)check)
        {
            hhook = NULL;
            return true;
        }
        return false;
    }

} // namespace key_hook

#endif