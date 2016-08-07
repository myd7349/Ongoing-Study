@echo off
REM SWIG utility for creating interface files.
REM By myd
REM 2016-04-22T15:25+08:00
REM Usage:
REM SWIGHelper.bat <namespace> <source swig interface file>

cmd /c swig -help > nul
if not errorlevel 0 goto SWIGNotFound

echo Invoking SWIG...
swig -c++ -csharp -namespace %1 -dllimport %1Native.dll -outdir "%~dp0%1" -outfile %1Native.cs "%2"
goto Finish

:SWIGNotFound
echo Command 'swig' not found.

:Finish
echo on