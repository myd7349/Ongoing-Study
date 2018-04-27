[How to install a NuGet package into a specified project?](https://stackoverflow.com/questions/4967651/how-do-i-install-a-nuget-package-into-the-second-project-in-a-solution)
```powershell
Get-Project SomeProject | Install-Package SomePackage
```