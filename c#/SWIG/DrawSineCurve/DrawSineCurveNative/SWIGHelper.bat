@echo off
REM SWIG utility for creating interface files.
REM By myd7349
REM 2016-04-22T15:25+08:00
REM Usage:
REM SWIGHelper.bat <namespace> <output wrapper code file> <source swig interface file>

cmd /c swig -help > nul
if not errorlevel 0 goto SWIGNotFound

echo Invoking SWIG...
swig -c++ -csharp -namespace %1 -dllimport %1Native -outdir "%~dp0..\%1" -outfile %2.cs "%3"
goto Finish

:SWIGNotFound
echo Command 'swig' not found.

:Finish
echo on