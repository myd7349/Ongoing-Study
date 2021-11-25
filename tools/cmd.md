Tools:

- [clink](https://github.com/mridgers/clink): Bash's powerful command line editing in cmd.exe

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

[How to check if a file exists from inside a batch file](https://stackoverflow.com/questions/4340350/how-to-check-if-a-file-exists-from-inside-a-batch-file)
[Batch - for loop inside for loop](https://stackoverflow.com/questions/23316289/batch-for-loop-inside-for-loop)
[http://www.trytoprogram.com/batch-file-functions/](http://www.trytoprogram.com/batch-file-functions/)
[Change Ownership of a File or Folder Using Takeown Command-Line Tool](https://www.winhelponline.com/blog/take-ownership-of-file-or-folder/)
[Delete files with denied access with batch scripts](https://www.tenforums.com/general-support/137910-question-delete-files-denied-access-batch-scripts.html)
https://stackoverflow.com/questions/8066679/how-to-do-a-simple-file-search-in-cmd
https://stackoverflow.com/questions/13680415/how-to-open-explorer-with-a-specific-file-selected
https://stackoverflow.com/questions/47450531/batch-write-output-of-dir-to-a-variable
https://stackoverflow.com/questions/13809856/run-reg-command-in-cmd-bat-file
https://answers.microsoft.com/en-us/windows/forum/windows8_1-security-winacc/how-to-delete-or-rename-files-protected-by/bb8f5a30-54c7-43dd-a450-48c972ceeeba
https://thegeekpage.com/how-to-delete-files-protected-by-trustedinstaller-in-windows-10/
[How to get folder path from file path with CMD](https://stackoverflow.com/questions/659647/how-to-get-folder-path-from-file-path-with-cmd)
[Cmd : not evaluating variables inside a loop](https://stackoverflow.com/questions/3987582/cmd-not-evaluating-variables-inside-a-loop)
[Top 10 DOS Batch tips (Yes, DOS Batch...)](https://weblogs.asp.net/jongalloway/top-10-dos-batch-tips-yes-dos-batch)
[Get filename from string-path?](https://stackoverflow.com/questions/10393248/get-filename-from-string-path)
[Returning string from external function batch](https://stackoverflow.com/questions/50304807/returning-string-from-external-function-batch)
[Batch Script - Functions](https://www.tutorialspoint.com/batch_script/batch_script_functions.htm)

[Batch file call sub-batch file to pass n paramenters and return without use of file](https://stackoverflow.com/questions/11481150/batch-file-call-sub-batch-file-to-pass-n-paramenters-and-return-without-use-of-f/25249059)

[remove last characters string batch](https://stackoverflow.com/questions/29503925/remove-last-characters-string-batch/29504048)

[Remove Trailing Slash From Batch File Input](https://stackoverflow.com/questions/2952401/remove-trailing-slash-from-batch-file-input/2952637)

[Menus in Batch File](https://stackoverflow.com/questions/19125913/menus-in-batch-file)()

[How to change text color of cmd with windows batch script every 1 second](https://stackoverflow.com/questions/12572718/how-to-change-text-color-of-cmd-with-windows-batch-script-every-1-second)

https://github.com/dbohdan/messagebox

> netstat  -ano | findstr "5037"
> 
> tasklist| findstr "34652"

https://github.com/SergeyPirogov/webdriver_manager/blob/master/webdriver_manager/utils.py

>  reg query "HKEY_CURRENT_USER\Software\Google\Chrome\BLBeacon" /v version

[How can I pass arguments to a batch file?](https://stackoverflow.com/questions/26551/how-can-i-pass-arguments-to-a-batch-file)

[How to "comment-out" (add comment) in a batch/cmd?](https://stackoverflow.com/questions/11269338/how-to-comment-out-add-comment-in-a-batch-cmd)

[What is the significance of a dot after a command in Batch?](https://superuser.com/questions/739041/what-is-the-significance-of-a-dot-after-a-command-in-batch)

[Something like a function/method in batch files?](https://stackoverflow.com/questions/10149194/something-like-a-function-method-in-batch-files)

[DOS Batch - Function Tutorial](https://www.dostips.com/DtTutoFunctions.php)

[How to use if - else structure in a batch file?](https://stackoverflow.com/questions/11081735/how-to-use-if-else-structure-in-a-batch-file)

[If](https://ss64.com/nt/if.html)

[Check if a string variable is empty in batch script](https://stackoverflow.com/questions/39679344/check-if-a-string-variable-is-empty-in-batch-script)

[Batch not-equal (inequality) operator](https://stackoverflow.com/questions/1421441/batch-not-equal-inequality-operator)

[What is the proper way to test if a parameter is empty in a batch file?](https://stackoverflow.com/questions/2541767/what-is-the-proper-way-to-test-if-a-parameter-is-empty-in-a-batch-file)

[IF ELSE syntax error within batch file?](https://stackoverflow.com/questions/25468488/if-else-syntax-error-within-batch-file)

[Square bracket notation around variable in cmd / DOS batch scripts](https://stackoverflow.com/questions/23552267/square-bracket-notation-around-variable-in-cmd-dos-batch-scripts)

[Parenthesis in variables inside IF blocks](https://stackoverflow.com/questions/11944074/parenthesis-in-variables-inside-if-blocks)

```
set xyz=123
if %xyz% == 123 ( echo [(^)] )
```

[windows batch SET inside IF not working](https://stackoverflow.com/questions/9102422/windows-batch-set-inside-if-not-working)

```
:: https://github.com/SkewwG/domainTools
reg query "HKLM\SOFTWARE\MICROSOFT\CRYPTOGRAPHY" /v "MachineGuid"
```

[How can I pass arguments to a batch file?](https://stackoverflow.com/questions/26551/how-can-i-pass-arguments-to-a-batch-file)

[Does %* in batch file mean all command line arguments?](https://superuser.com/questions/149951/does-in-batch-file-mean-all-command-line-arguments)
