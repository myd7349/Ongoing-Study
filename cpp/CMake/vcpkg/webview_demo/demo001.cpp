#define WEBVIEW_WINAPI
#define WEBVIEW_IMPLEMENTATION
#include "webview.h"

#ifdef WINDOWS
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
    int nCmdShow) {
#else

#ifdef _WIN32
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#endif

int main() {
#endif
    /* Open wikipedia in a 800x600 resizable window */
    webview("Minimal webview example",
        "https://github.com/", 800, 600, 1);
    return 0;
}


// References:
// https://github.com/zserge/webview
