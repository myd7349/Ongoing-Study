[correct quoting for cmd.exe for multiple arguments](https://stackoverflow.com/questions/12891383/correct-quoting-for-cmd-exe-for-multiple-arguments)

[Multiple line command](https://github.com/zhihaoy/cpp-argparse-feedstock/blob/master/recipe/bld.bat)
```bat
cmake -G Ninja ^
  -DCMAKE_INSTALL_PREFIX=%LIBRARY_PREFIX% ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DARGPARSE_BUILD_TESTS=OFF ^
  %SRC_DIR%
```

[How to get return/exit code of a batch file started with START command?](https://stackoverflow.com/questions/42597703/how-to-get-return-exit-code-of-a-batch-file-started-with-start-command)
> cmd /v /e /c "start /high /wait cmd /c launched.cmd & exit ^!errorlevel^!"

[How do I get current date/time on the Windows command line in a suitable format for usage in a file/folder name?](https://stackoverflow.com/questions/203090/how-do-i-get-current-date-time-on-the-windows-command-line-in-a-suitable-format)

[Setting a windows batch file variable to the day of the week](https://stackoverflow.com/questions/11364147/setting-a-windows-batch-file-variable-to-the-day-of-the-week)

[Format date and time in a Windows batch script](https://stackoverflow.com/questions/1192476/format-date-and-time-in-a-windows-batch-script)
