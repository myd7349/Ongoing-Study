:: https://github.com/schoetbi/XPTable/blob/master/createGitStatus.bat
git log --pretty=oneline -n1 > %1
git status >> %1

set puredate=%date:~,10%
set mydate=%puredate:/=-%
set mytime=%time: =0%

git rev-parse --short HEAD > githash.txt
set /p HASH=<githash.txt
echo using System.Reflection; > %2
echo [assembly: AssemblyInformationalVersion("%HASH%(%mydate% %mytime%)")] >> %2
