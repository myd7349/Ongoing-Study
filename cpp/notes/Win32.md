Toast Notification

- [ToastNotifications](https://github.com/rafallopatka/ToastNotifications)

- [TwitchNotify/WindowsToast.h at master · mmozeiko/TwitchNotify · GitHub](https://github.com/mmozeiko/TwitchNotify/blob/master/WindowsToast.h)

- [WinToast](https://github.com/mohabouje/WinToast)

Printing

- [Q193943: HOWTO: Use GetDeviceCaps to Determine Margins on a Page | KnowledgeBase Archive](https://jeffpar.github.io/kbarchive/kb/193/Q193943/)
  
  > ```
  >         Private Const HORZRES = 8
  >         Private Const VERTRES = 10
  >         Private Const LOGPIXELSX = 88
  >         Private Const LOGPIXELSY = 90
  >         Private Const PHYSICALWIDTH = 110
  >         Private Const PHYSICALHEIGHT = 111
  >         Private Const PHYSICALOFFSETX = 112
  >         Private Const PHYSICALOFFSETY = 113
  > ```
  
  For example:
  
  - Microsoft Print to PDF
    
    ```
    GetDeviceCaps(HORZSIZE) == 297
    GetDeviceCaps(VERTSIZE) == 210
    GetDeviceCaps(HORZRES) == 7016
    GetDeviceCaps(VERTRES) == 4961
    GetDeviceCaps(LOGPIXELSX) == 600
    GetDeviceCaps(LOGPIXELSY) == 600
    GetDeviceCaps(PHYSICALWIDTH) == 7016
    GetDeviceCaps(PHYSICALHEIGHT) == 4961
    GetDeviceCaps(PHYSICALOFFSETX) == 0
    GetDeviceCaps(PHYSICALOFFSETY) == 0
    ```
  
  - HP LaserJet 400 M401 PCL 6, a real printer
    
    ```
    GetDeviceCaps(HORZSIZE) == 289
    GetDeviceCaps(VERTSIZE) == 202
    GetDeviceCaps(HORZRES) == 6815
    GetDeviceCaps(VERTRES) == 4760
    GetDeviceCaps(LOGPIXELSX) == 600
    GetDeviceCaps(LOGPIXELSY) == 600
    GetDeviceCaps(PHYSICALWIDTH) == 7015
    GetDeviceCaps(PHYSICALHEIGHT) == 4960
    GetDeviceCaps(PHYSICALOFFSETX) == 100
    GetDeviceCaps(PHYSICALOFFSETY) == 100
    ```
  
  Both of the printers above have a 600 DPI resolution.
  
  > 7016 ÷ 600 × 2.54 = 29.701cm
  > 
  > 4961 ÷ 600 × 2.54 = 21.0cm
  > 
  > 6815  ÷  600  ×  2.54 = 28.8501cm
  > 
  > 4760  ÷  600  ×  2.54 = 20.15cm
  > 
  > 100 ÷ 600 × 2.54 = 0.423333cm

- [Printing does not start at the top edge of the page](https://stackoverflow.com/questions/21448977/printing-does-not-start-at-the-top-edge-of-the-page)

ImageBase

- C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29333\crt\src\vcruntime\exe_common.inl
  
  > ```cpp
  > #elif defined _SCRT_STARTUP_WINMAIN
  > 
  >     using main_policy = __scrt_winmain_policy;
  >     using file_policy = __scrt_file_policy;
  >     using argv_policy = __scrt_narrow_argv_policy;
  >     using environment_policy = __scrt_narrow_environment_policy;
  > 
  >     static int __cdecl invoke_main()
  >     {
  >         return WinMain(
  >             reinterpret_cast<HINSTANCE>(&__ImageBase),
  >             nullptr,
  >             _get_narrow_winmain_command_line(),
  >             __scrt_get_show_window_mode());
  >     }
  > 
  > #elif defined _SCRT_STARTUP_WWINMAIN
  > ```

AttachConsole used in [PyStand/PyStand.cpp at 654066cd6162787cf5d72d3f4274f5aea5dc14d8 · skywind3000/PyStand · GitHub](https://github.com/skywind3000/PyStand/blob/654066cd6162787cf5d72d3f4274f5aea5dc14d8/PyStand.cpp#L345)

- [Using AttachConsole, user must hit enter to get regular command line](https://stackoverflow.com/questions/1305257/using-attachconsole-user-must-hit-enter-to-get-regular-command-line)

- [c# - Can one executable be both a console and GUI application? - Stack Overflow](https://stackoverflow.com/questions/493536/can-one-executable-be-both-a-console-and-gui-application/494000#494000)