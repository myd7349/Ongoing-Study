#include "winlamb/window_main.h"

class My_Window : public wl::window_main {
public:
    My_Window();
};

RUN(My_Window) // optional, generate WinMain call and instantiate My_Window

My_Window::My_Window()
{
    setup.wndClassEx.lpszClassName = L"SOME_CLASS_NAME"; // class name to be registered
    setup.title = L"This is my window";
    setup.style |= WS_MINIMIZEBOX;

    on_message(WM_CREATE, [this](wl::wm::create p) -> LRESULT
    {
        set_text(L"A new title for the window");
        return 0;
    });

    on_message(WM_LBUTTONDOWN, [](wl::wm::lbuttondown p) -> LRESULT
    {
        bool isCtrlDown = p.has_ctrl();
        long xPos = p.pos().x;
        return 0;
    });
}
