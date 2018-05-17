:: 2018-05-17T11:15+08:00
:: By myd7349

:: %1 is the path of `msbuild.exe`.
%1 "%~dp0NativeLib.vcxproj" /p:Configuration=Release /p:Platform=Win32
%1 "%~dp0NativeLib.vcxproj" /p:Configuration=Release /p:Platform=x64

:: References:
:: https://stackoverflow.com/questions/2839221/how-do-i-create-a-makefile-from-a-visual-studio-solution-file
:: https://stackoverflow.com/questions/8794379/how-or-why-is-msbuild-choosing-the-x64-platform-when-i-dont-specify-it-instead
:: https://stackoverflow.com/questions/27090144/how-do-i-use-msbuild-in-visual-studios-post-build-event
:: https://stackoverflow.com/questions/10508778/postbuildevent-create-directory
