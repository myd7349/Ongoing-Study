[correct quoting for cmd.exe for multiple arguments](https://stackoverflow.com/questions/12891383/correct-quoting-for-cmd-exe-for-multiple-arguments)

[Multiple line command](https://github.com/zhihaoy/cpp-argparse-feedstock/blob/master/recipe/bld.bat)
```bat
cmake -G Ninja ^
  -DCMAKE_INSTALL_PREFIX=%LIBRARY_PREFIX% ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DARGPARSE_BUILD_TESTS=OFF ^
  %SRC_DIR%
```
