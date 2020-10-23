#ifndef key_proc
#define key_proc

#include <iostream>
#include <winuser.h>
#include "key_codes.h"
using namespace std;

namespace key_proc
{
    INPUT change_ks(DWORD vkey)
    {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = vkey;
        input.ki.dwFlags = KEYEVENTF_UNICODE;

        return input;
    }

    LRESULT CALLBACK kbdproc(int code, WPARAM wparam, LPARAM lparam)
    {
        if (code < 0)
            return CallNextHookEx(NULL, code, wparam, lparam);

        KBDLLHOOKSTRUCT *k = ((KBDLLHOOKSTRUCT *)lparam);
        if (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
        {
            cout << key_codes::kc[k->vkCode].desc;
            if (k->vkCode == VK_RETURN)
                cout << "\n";
        }

        if (wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
        {
            if (k->vkCode == VK_CAPITAL || k->vkCode == VK_NUMLOCK ||
                k->vkCode == VK_LCONTROL || k->vkCode == VK_LMENU || k->vkCode == VK_LSHIFT || k->vkCode == VK_LWIN ||
                k->vkCode == VK_RCONTROL || k->vkCode == VK_RMENU || k->vkCode == VK_RSHIFT || k->vkCode == VK_RWIN)

                for (auto i = 0; i < key_codes::kc[k->vkCode].desc.length(); i++)
                {
                    if (i == 1)
                        cout << "\\";
                    cout << key_codes::kc[k->vkCode].desc[i];
                }
        }

        /*if (wparam == WM_KEYDOWN && ((KBDLLHOOKSTRUCT *)lparam)->vkCode == VK_OEM_MINUS)
        {
            INPUT input = change_ks(VK_ADD);
            SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));

            return 1;
        }*/

        return CallNextHookEx(NULL, code, wparam, lparam);
    }

} // namespace key_proc

#endif