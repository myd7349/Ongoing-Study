1. [How to install a NuGet package into a specified project?](https://stackoverflow.com/questions/4967651/how-do-i-install-a-nuget-package-into-the-second-project-in-a-solution)
   
   > Get-Project SomeProject | Install-Package SomePackage
   
   Or:
   
   > Install-Package SomePackage -Version 1.0.0 -Project SomeProject

2. [Automatic NuGet package generation](https://github.com/HDFGroup/HDF.PInvoke/pull/106)
   
   [CircularBuffer-CSharp](https://github.com/joaoportela/CircularBuffer-CSharp/tree/master/.github/workflows)

3. repositories.config
   
   - [NuGet - repositories.config](https://stackoverflow.com/questions/7286261/nuget-repositories-config)
   - [What is the Nuget repositories.config file for?](https://stackoverflow.com/questions/11207635/what-is-the-nuget-repositories-config-file-for)

4. [Multi-targeting for NuGet Packages in your project file](https://docs.microsoft.com/en-us/nuget/create-packages/supporting-multiple-target-frameworks)

5. [.NET project SDKs](https://docs.microsoft.com/en-us/dotnet/core/project-sdk/overview)

6. https://github.com/devlooped/nugetizer

7. https://github.com/squid-box/SevenZipSharp

8. https://github.com/fo-dicom/fo-dicom/tree/development/Setup

9. [NuGet: 'X' already has a dependency defined for 'Y'](https://stackoverflow.com/questions/25725545/nuget-x-already-has-a-dependency-defined-for-y)
   
   In VS2010, `Install-Package FlaUI.Core` failed:
   
   > <MyProject> already has a dependency defined for `Microsoft.Win32.Registry`.
   
   > I faced this error on outdated version of Visual Studio 2010. Due to  project configuration I was not able to update this version to newer.  Therefore, update of NuGet advised above did not fix things for me. 
   > 
   > Root reason for the error in this and similar situations is in  dependencies of the package you try to install, which are not compatible with .NET version available in your project. 
   > 
   > Universal solution is not obligatory update of Visual Studio or .NET  but in installation of older NuGet versions of the same package  compatible with your system. 
   > 
   > It is not possible to tell for sure, which of earlier versions will  work. In my case, this command installed the package without any NuGet  updates.
   > 
   > ```powershell
   > Install-Package X -Version [compatible version number]
   > ```
   
   and another answer:
   
   > 1. Go to the link https://www.nuget.org/packages/
   > 2. Search your NuGet packages 
   > 3. See the all version of related packages
   > 4. Install the lower version of packages
   
   at last:
   
   > Install-Package FlaUI.Core -Version 2.0.0-rc1
   
   works for me.

10. [NuGet: Update a package to a specific version in all projects via PowerShell or CMD](https://stackoverflow.com/questions/39574042/nuget-update-a-package-to-a-specific-version-in-all-projects-via-powershell-or)
    
    > Update-Package FastReport.OpenSource -Version 2020.3.0
    
    [Reinstalling and Updating NuGet Packages | Microsoft Docs](https://docs.microsoft.com/en-us/nuget/consume-packages/reinstalling-and-updating-packages)

11. https://github.com/xoofx/dotnet-releaser

12. [Package authoring best practices](https://learn.microsoft.com/en-us/nuget/create-packages/package-authoring-best-practices)
