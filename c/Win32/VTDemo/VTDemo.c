#include <stdio.h>

#include <windows.h>


#define ESC "\x1b"
#define CSI "\x1b["


void GotoXY(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


BOOL EnableVTMode(void)
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return FALSE;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return FALSE;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
        return FALSE;

    return TRUE;
}


void VTGotoXY(int x, int y)
{
    printf(ESC "[%d;%df", y, x);
}


int main(void)
{
    if (!EnableVTMode())
        return GetLastError();

    GotoXY(10, 10);
    printf("Hello, world!");

    VTGotoXY(30, 20);
    printf(CSI "32mHello, world!");
    printf(CSI "m");

    return 0;
}

// References:
// [在控制台应用程序中，如何cout到屏幕的指定位置，比如几行几列？](https://www.zhihu.com/question/20345107/answer/389212043)
// Belleve:
// > 我建议你更新下答案，现在 Console Team 极度反对继续使用 SetConsoleCursorPosition 之类 Console API，而是使用 VT 序列。
//   使用 SetConsoleMode(handle, ENABLE_VIRTUAL_TERMINAL_PROCESSING) 打开 VT，然后用 \x33<行>,<列>f 移动光标。
// [Console Virtual Terminal Sequences](https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences)
// [Console Virtual Terminal Sequences](https://github.com/MicrosoftDocs/Console-Docs/blob/master/docs/console-virtual-terminal-sequences.md)
// [How to make win32 console recognize ANSI/VT100 escape sequences?](https://stackoverflow.com/questions/16755142/how-to-make-win32-console-recognize-ansi-vt100-escape-sequences)
// https://github.com/s9w/oof#performance--os-specific-details
