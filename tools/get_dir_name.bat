@call :get_dir_name dir1, "C:\Windows\System32\notepad.exe"
@echo %dir1%

@call :get_dir_name dir1, "C:\Windows\System32\DriverStore\FileRepository\msmouse.inf_amd64_1793a485b491b199\sermouse.sys"
@echo %dir1%

@pause

:get_dir_name
@set "%~1=%~dp2"
@exit /b 0
