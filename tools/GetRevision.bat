:: Usage:
:: GetRevision.bat VERSION.txt SVN.Revision.txt AssemblyInfo.Revision.cs

setlocal EnableDelayedExpansion

if exist "%1" (
    set /p FILE_VERSION=<"%1"
) else (
    set FILE_VERSION=
)

where svn
if %ERRORLEVEL% neq 0 then (
    echo svn command wasn't found.
    set SVN_REVISION=
) else (
    svn info | findstr "Revision:" > "%2"
    set /p SVN_REVISION_LINE=<"%2"
    if "%SVN_REVISION_LINE%" == "" (
        set SVN_REVISION=
    ) else (
        set SVN_REVISION=r%SVN_REVISION_LINE:~10,10%
    )
)

set puredate=%date:~,10%
set mydate=%puredate:/=-%
set mytime=%time: =0%

echo using System.Reflection; > "%3"
echo [assembly: AssemblyInformationalVersion("%SVN_REVISION%(%mydate% %mytime%)"^)] >> "%3"

if not "%FILE_VERSION%" == "" (
    echo [assembly: AssemblyVersion("%FILE_VERSION%"^)] >> "%3"
    echo [assembly: AssemblyFileVersion("%FILE_VERSION%"^)] >> "%3"
)


:: References:
:: [Determine if command is recognized in a batch file](https://superuser.com/questions/175466/determine-if-command-is-recognized-in-a-batch-file)
:: [How to extract part of a string in Windows batch file?](https://superuser.com/questions/228794/how-to-extract-part-of-a-string-in-windows-batch-file)
:: [How to set commands output as a variable in a batch file](https://stackoverflow.com/questions/6359820/how-to-set-commands-output-as-a-variable-in-a-batch-file)
:: [Batch findstr to find a number](https://stackoverflow.com/questions/14255970/batch-findstr-to-find-a-number)
