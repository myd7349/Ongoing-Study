[What is the difference between _chdir and SetCurrentDirectory in windows?](https://stackoverflow.com/questions/7544153/what-is-the-difference-between-chdir-and-setcurrentdirectory-in-windows)

> `_chdir` actually uses `SetCurrentDirectory` internally, so on most cases they are effectively interchangeable. However, `_chdir` does one more thing: it updates the current directory of the current 
> drive, stored in an environment variable. This is needed, as the remark 
> in `_tchdir` states, because "other functions (fullpath, spawn, etc) need them to be set".
> 
> I'm not sure how much this is needed these days, but I would say - if
>  you're using those POSIX-style functions for file operations, path 
> manipulation, process creation etc., use `_chdir` accordingly. If you're using Win32 API functions directly, use `SetCurrentDirectory`.

[Somthing of bad understanding in "SetCurrentDirectory" ("windows.h") in CPP](https://stackoverflow.com/questions/41433608/somthing-of-bad-understanding-in-setcurrentdirectory-windows-h-in-cpp)

[Why does each drive have its own current directory? - The Old New Thing](https://devblogs.microsoft.com/oldnewthing/20101011-00/?p=12563)
