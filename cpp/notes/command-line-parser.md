1. About `argc` and `argv`
   
   - [Defining own main functions arguments argc and argv](https://stackoverflow.com/questions/1519885/defining-own-main-functions-arguments-argc-and-argv)
   
   - [Creating your own char **argv](https://www.daniweb.com/programming/software-development/threads/476677/creating-your-own-char-argv)
     
     > ```c
     > #include <stdarg.h>
     > char **new_argv(int count, ...)
     > {
     >     va_list args;
     >     int i;
     >     char **argv = malloc((count+1) * sizeof(char*));
     >     char *temp;
     >     va_start(args, count);
     >     for (i = 0; i < count; i++) {
     >         temp = va_arg(args, char*);
     >         argv[i] = malloc(sizeof(temp));
     >         argv[i] = temp;
     >     }
     >     argv[i] = NULL;
     >     va_end(args);
     >     return argv;
     > }
     > ```
   
   - Handle command line arguments in MFC
     
     [How is the CommandLineToArgvW function intended to be used?](https://devblogs.microsoft.com/oldnewthing/20100916-00/?p=12843)
     
     [What's up with the strange treatment of quotation marks and backslashes by CommandLineToArgvW](https://devblogs.microsoft.com/oldnewthing/20100917-00/?p=12833)
     
     [How to get the command line arguments in MFC applications?](https://stackoverflow.com/questions/5562877/how-to-get-the-command-line-arguments-in-mfc-applications)
     
     https://github.com/reactos/reactos/blob/be8e5fc7b31d64732a0ffd37a27d580c68c76ac5/dll/win32/shell32/wine/shell32_main.c#L80-L311
     
     > ```c++
     > PWSTR pszCommandLine = GetCommandLineW();
     > 
     > int argc;
     > PWSTR *argv = CommandLineToArgvW(pszCommandLine, &argc);
     > if (argv == nullptr)
     >  return;
     > 
     > // ...
     > my_main(argc, argv);
     > 
     > LocalFree(argv);
     > ```
   
   - [Canonical way to parse the command line into arguments in plain C Windows API](https://stackoverflow.com/questions/291424/canonical-way-to-parse-the-command-line-into-arguments-in-plain-c-windows-api)
     
     > ```c
     > LPSTR* CommandLineToArgvA(LPSTR lpCmdLine, INT *pNumArgs)
     > {
     >     int retval;
     >     retval = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, NULL, 0);
     >     if (!SUCCEEDED(retval))
     >         return NULL;
     > 
     >     LPWSTR lpWideCharStr = (LPWSTR)malloc(retval * sizeof(WCHAR));
     >     if (lpWideCharStr == NULL)
     >         return NULL;
     > 
     >     retval = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, lpWideCharStr, retval);
     >     if (!SUCCEEDED(retval))
     >     {
     >         free(lpWideCharStr);
     >         return NULL;
     >     }
     > 
     >     int numArgs;
     >     LPWSTR* args;
     >     args = CommandLineToArgvW(lpWideCharStr, &numArgs);
     >     free(lpWideCharStr);
     >     if (args == NULL)
     >         return NULL;
     > 
     >     int storage = numArgs * sizeof(LPSTR);
     >     for (int i = 0; i < numArgs; ++ i)
     >     {
     >         BOOL lpUsedDefaultChar = FALSE;
     >         retval = WideCharToMultiByte(CP_ACP, 0, args[i], -1, NULL, 0, NULL, &lpUsedDefaultChar);
     >         if (!SUCCEEDED(retval))
     >         {
     >             LocalFree(args);
     >             return NULL;
     >         }
     > 
     >         storage += retval;
     >     }
     > 
     >     LPSTR* result = (LPSTR*)LocalAlloc(LMEM_FIXED, storage);
     >     if (result == NULL)
     >     {
     >         LocalFree(args);
     >         return NULL;
     >     }
     > 
     >     int bufLen = storage - numArgs * sizeof(LPSTR);
     >     LPSTR buffer = ((LPSTR)result) + numArgs * sizeof(LPSTR);
     >     for (int i = 0; i < numArgs; ++ i)
     >     {
     >         assert(bufLen > 0);
     >         BOOL lpUsedDefaultChar = FALSE;
     >         retval = WideCharToMultiByte(CP_ACP, 0, args[i], -1, buffer, bufLen, NULL, &lpUsedDefaultChar);
     >         if (!SUCCEEDED(retval))
     >         {
     >             LocalFree(result);
     >             LocalFree(args);
     >             return NULL;
     >         }
     > 
     >         result[i] = buffer;
     >         buffer += retval;
     >         bufLen -= retval;
     >     }
     > 
     >     LocalFree(args);
     > 
     >     *pNumArgs = numArgs;
     >     return result;
     > }
     > ```

2. Libraries
   
   - [argparse](https://github.com/cofyc/argparse) - C
- [argparse](https://github.com/p-ranav/argparse) - C++
  
  - CLI11

- [cmdline](https://github.com/tanakh/cmdline)
  
  - docopt.cpp

- gflags
  
  - https://github.com/polybar/polybar/blob/master/include/components/command_line.hpp
    
    - https://github.com/danmar/checkheaders/blob/master/src/main.cpp

- https://github.com/ros2/rcutils/blob/master/include/rcutils/cmdline_parser.h
  
  - https://github.com/MayaPosch/Sarge

- https://github.com/hasherezade/paramkit
  
  - https://github.com/hasherezade/pe-sieve
    - https://chromium.googlesource.com/chromium/src/+/refs/heads/main/base/command_line.h

- https://github.com/moya-lang/Arguments
  
  - [Parsing Command Line Arguments in C++?](https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c)
    
    - [TCLAP](http://tclap.sourceforge.net/)
      
      - https://github.com/BYVoid/OpenCC/blob/master/src/tools/CommandLine.cpp

      - https://github.com/Inria-Asclepios/LCC-LogDemons
      
      - [CLAP](https://www.cs.bgu.ac.il/~cgproj/CLAP/)

      - [MGARD](https://github.com/CODARcode/MGARD)

- GNU getopt
  
  - https://github.com/r4start/getoptpp
    - https://github.com/microsoft/VisualTrueType/blob/main/src/getopt.h
  - https://github.com/wolfpld/tracy/blob/master/capture/src/capture.cpp
    - [getopt_long() -- proper way to use it?](https://stackoverflow.com/questions/7489093/getopt-long-proper-way-to-use-it)
  - [Argument-parsing helpers for C/Unix](https://stackoverflow.com/questions/189972/argument-parsing-helpers-for-c-unix)
    > GNU has [gengetopt](https://www.gnu.org/software/gengetopt/) which generates code for an options data structure and the getopt_long code to parse the command line and fill the structure.
  - https://github.com/zint/zint
  - https://github.com/wolfpld/tracy

- popt
  
  - https://github.com/stephenegriffin/EnumAccounts/blob/master/main.cpp

- https://github.com/nihui/waifu2x-ncnn-vulkan/blob/master/src/main.cpp
  
  - [flags](https://github.com/google/neper/blob/master/flags.c)

- https://github.com/auscaster/cpp-optparse

- https://github.com/nanomsg/nng/blob/master/src/supplemental/util/options.c

- https://github.com/procxx/cxx20opts

- https://github.com/flameshot-org/flameshot/blob/master/src/cli/commandlineparser.h

- https://github.com/Jeroen6/bin2c/blob/original/src/main.c

- https://github.com/abolz/CmdLine

- https://github.com/abolz/CmdLine2

- https://github.com/muellan/clipp

- https://github.com/git/git/blob/master/http.c

- https://github.com/krychu/wfc/blob/master/wfctool.c

- https://keep.imfreedom.org/pidgin/pidgin/file/tip/pidgin/win32/winpidgin.c

- TortoiseGit\src\Utils\CmdLineParser.h

- [Parsing command-line arguments in C](https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c)

- https://github.com/dberlin/superfuzz/blob/master/include/option.h

- https://github.com/vivaladav/cpu-stat/blob/master/src/OptionsParser.h

- https://github.com/electron/rcedit/blob/master/src/main.cc
