[libsodium-nupkg](https://github.com/jedisct1/libsodium/issues/775)

[nuget-gflags](https://github.com/gflags/nuget-gflags)

[How do I install a NuGet package into the second project in a solution?](https://stackoverflow.com/questions/4967651/how-do-i-install-a-nuget-package-into-the-second-project-in-a-solution)
> Get-Project SomeProject | Install-Package SomePackage

or
> Install-Package SomePackage -Project MvcApplication2

[NuGet behind a proxy](https://stackoverflow.com/questions/9232160/nuget-behind-a-proxy)

[Accessing Nuget Official Package Source behind company proxy](https://stackoverflow.com/questions/7710533/accessing-nuget-official-package-source-behind-company-proxy)

[Package authoring best practices](https://docs.microsoft.com/en-us/nuget/create-packages/package-authoring-best-practices)

[How do I get NuGet to install/update all the packages in the packages.config?](https://stackoverflow.com/questions/6876732/how-do-i-get-nuget-to-install-update-all-the-packages-in-the-packages-config)

> ```
> nuget restore YourSolution.sln
> ```

or

> ```
> nuget install packages.config
> ```

