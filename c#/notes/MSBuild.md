- [Including content files in .csproj that are outside the project cone](https://stackoverflow.com/questions/1292351/including-content-files-in-csproj-that-are-outside-the-project-cone)

- [Your  project does not reference ".NETFramework,Version=v4.6.2" framework.  Add a reference to ".NETFramework,Version=v4.6.2" in the  "TargetFrameworks"](https://stackoverflow.com/questions/52833741/your-project-does-not-reference-netframework-version-v4-6-2-framework-add-a)

  > Please make the next steps
  >
  > 1. Clean solution 
  > 2. Clean folder "packages" 
  > 3. Delete folder "bin" 
  > 4. Delete folder "obj"

- [How do I exclude files/folders from a .NET Core/Standard project?](https://stackoverflow.com/questions/43173811/how-do-i-exclude-files-folders-from-a-net-core-standard-project)

  > ```xml
  > <PropertyGroup>
  >   <DefaultItemExcludes>$(DefaultItemExcludes);your_nonproj.file;a\**\*.pattern</DefaultItemExcludes>
  > </PropertyGroup>
  > ```

- https://github.com/daveaglick/Buildalyzer
