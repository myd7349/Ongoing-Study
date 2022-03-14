[AssemblyResolve](https://github.com/microsoft/perfview/blob/main/src/HeapDump/Program.cs)

[greenshot/GreenshotMain.cs at 82b37bcaa4b051313dbe28cab84863fc0c048dd5 · greenshot/greenshot · GitHub](https://github.com/greenshot/greenshot/blob/82b37bcaa4b051313dbe28cab84863fc0c048dd5/src/Greenshot/GreenshotMain.cs#L35-L57)

> ```csharp
> static GreenshotMain()
> {
>     AppDomain.CurrentDomain.AssemblyResolve += CurrentDomain_AssemblyResolve;
> }
> 
> private static Assembly CurrentDomain_AssemblyResolve(object sender, ResolveEventArgs args)
> {
>     Assembly ayResult = null;
>     string sShortAssemblyName = args.Name.Split(',')[0];
>     Assembly[] ayAssemblies = AppDomain.CurrentDomain.GetAssemblies();
>     foreach (Assembly ayAssembly in ayAssemblies)
>     {
>         if (sShortAssemblyName != ayAssembly.FullName.Split(',')[0])
>         {
>             continue;
>         }
> 
>         ayResult = ayAssembly;
>         break;
>     }
> 
>     return ayResult;
> }
> ```

https://github.com/chocolatey/ChocolateyGUI/blob/1.0.0/Source/ChocolateyGui/App.xaml.cs#L36-L94
