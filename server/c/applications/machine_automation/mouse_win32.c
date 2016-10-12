#include <windows.h>
#include <sequanto/types.h>

#include "config.h"

static DWORD mouse_get_mouse_event_flags(int _button, SQBool _up)
{
    switch (_button)
    {
    case 1:
        switch (_up)
        {
        case SQ_TRUE:
            return MOUSEEVENTF_RIGHTUP;

        default:
            return MOUSEEVENTF_RIGHTDOWN;
        }

    case 2:
        switch (_up)
        {
        case SQ_TRUE:
            return MOUSEEVENTF_MIDDLEUP;

        default:
            return MOUSEEVENTF_MIDDLEDOWN;
        }

    default:
        switch (_up)
        {
        case SQ_TRUE:
            return MOUSEEVENTF_LEFTUP;

        default:
            return MOUSEEVENTF_LEFTDOWN;
        }
    }
}

void mouse_click_at(int _x, int _y, int _button)
{
    INPUT input;

    SetCursorPos(_x, _y);

    input.type = INPUT_MOUSE;
    input.mi.dx = _x;
    input.mi.dy = _y;
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | mouse_get_mouse_event_flags(_button, SQ_FALSE);
    input.mi.time = 0;
    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));

    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | mouse_get_mouse_event_flags(_button, SQ_TRUE);
    SendInput(1, &input, sizeof(INPUT));
}

void mouse_hold_at(int _x, int _y, int _button)
{
    INPUT input;

    SetCursorPos(_x, _y);

    input.type = INPUT_MOUSE;
    input.mi.dx = _x;
    input.mi.dy = _y;
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | mouse_get_mouse_event_flags(_button, SQ_FALSE);
    input.mi.time = 0;
    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));
}

void mouse_release_at(int _x, int _y, int _button)
{
    INPUT input;

    SetCursorPos(_x, _y);

    input.type = INPUT_MOUSE;
    input.mi.dx = _x;
    input.mi.dy = _y;
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | mouse_get_mouse_event_flags(_button, SQ_TRUE);
    input.mi.time = 0;
    input.mi.mouseData = 0;
    input.mi.dwExtraInfo = 0;
    SendInput(1, &input, sizeof(INPUT));
}
