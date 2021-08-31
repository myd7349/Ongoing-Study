1. Single File Executable

   - https://github.com/Fody/Costura

     > In .NET Core 3 there are two new features:
     >
     > - [Single-file executables](https://docs.microsoft.com/en-us/dotnet/core/whats-new/dotnet-core-3-0#single-file-executables)

   - https://github.com/antfu/live-draw#publish

     > dotnet publish -c Release -r win-x86 -p:PublishSingleFile=true
     >
     > dotnet publish -c Release -r win-x64 -p:PublishSingleFile=true