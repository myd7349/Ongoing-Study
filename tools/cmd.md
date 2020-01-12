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
