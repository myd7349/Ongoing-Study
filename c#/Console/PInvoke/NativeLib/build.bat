:: 2018-05-17T11:15+08:00
:: By myd7349

msbuild NativeLib.vcxproj /p:Configuration=Release /p:Platform=Win32
msbuild NativeLib.vcxproj /p:Configuration=Release /p:Platform=x64

:: References:
:: https://stackoverflow.com/questions/2839221/how-do-i-create-a-makefile-from-a-visual-studio-solution-file
:: https://stackoverflow.com/questions/8794379/how-or-why-is-msbuild-choosing-the-x64-platform-when-i-dont-specify-it-instead
