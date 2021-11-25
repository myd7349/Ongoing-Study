:: Usage:
:: GetVersion.bat cpp VERSION.txt githash.txt GitVersion.h
:: GetVersion.bat csharp VERSION.txt githash.txt AssemblyInfo.githash.cs

setlocal EnableDelayedExpansion

if exist "%2" (
    set /p FILE_VERSION=<"%2"
) else (
    set FILE_VERSION=
)

set puredate=%date:~,10%
set mydate=%puredate:/=-%
set mytime=%time: =0%

git rev-parse --short HEAD > "%3"
set /p GIT_HASH=<"%3"

if "%1" == "cpp" (
    echo #define PRODUCT_VERSION "%GIT_HASH%(%mydate% %mytime%)" > "%4"

    if not "%FILE_VERSION%" == "" (
        echo #define FILE_VERSION "%FILE_VERSION%" >> "%4"
        set FILE_VERSION_COMMA_SEPERATED=!FILE_VERSION:.=,!
        echo #define FILE_VERSION_COMMA_SEPERATED !FILE_VERSION_COMMA_SEPERATED! >> "%4"
    )
)

if "%1" == "csharp" (
    echo using System.Reflection; > "%4"
    echo [assembly: AssemblyInformationalVersion("%GIT_HASH%(%mydate% %mytime%)"^)] >> "%4"

    if not "%FILE_VERSION%" == "" (
        echo [assembly: AssemblyVersion("%FILE_VERSION%"^)] >> "%4"
        echo [assembly: AssemblyFileVersion("%FILE_VERSION%"^)] >> "%4"
    )
)

:: References:
:: https://github.com/schoetbi/XPTable/blob/master/createGitStatus.bat
:: https://github.com/flameshot-org/flameshot/blob/ce336a6a70725ba47db54092026caab8c1f84c52/src/CMakeLists.txt#L221
:: [Parenthesis in variables inside IF blocks](https://stackoverflow.com/questions/11944074/parenthesis-in-variables-inside-if-blocks)
:: [windows batch SET inside IF not working](https://stackoverflow.com/questions/9102422/windows-batch-set-inside-if-not-working/9102569)
:: https://github.com/3F/DllExport/blob/v1.7.4/DllExportVersion.cs
:: [How to specify the assembly version for a .NET Core project?](https://stackoverflow.com/questions/58433665/how-to-specify-the-assembly-version-for-a-net-core-project)
:: [Get date and time on the same line](https://stackoverflow.com/questions/20246889/get-date-and-time-on-the-same-line)
