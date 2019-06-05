#pragma once

#include <assert.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


enum KEY_STATES
{
    KEY_STATES_NONE    = 0,
    KEY_STATES_DOWN    = 1,
    KEY_STATES_TOGGLED = 2,
};


inline KEY_STATES GetKeyStates(int nVirtualKeyCode)
{
    assert(nVirtualKeyCode > 0 && nVirtualKeyCode < 255);

    int iKeyState = GetKeyState(nVirtualKeyCode);
    
    KEY_STATES states = KEY_STATES_NONE;
    if ((iKeyState & 32768) == 32768)
        states = (KEY_STATES)(states | KEY_STATES_DOWN);

    if ((iKeyState & 1) == 1)
        states = (KEY_STATES)(states | KEY_STATES_TOGGLED);

    return states;
}


inline BOOL IsKeyDown(int nVirtualKeyCode)
{
    return (GetKeyStates(nVirtualKeyCode) & KEY_STATES_DOWN) != 0;
}


inline BOOL IsKeyToggled(int nVirtualKeyCode)
{
    return (GetKeyStates(nVirtualKeyCode) & KEY_STATES_TOGGLED) != 0;
}


inline BOOL IsKeyUp(int nVirtualKeyCode)
{
    return !IsKeyDown(nVirtualKeyCode);
}


// References:
// https://github.com/raysan5/raylib/issues/535
