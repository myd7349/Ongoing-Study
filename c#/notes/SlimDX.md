[Microsoft DirectX Sound on Visual Studio 2017](https://stackoverflow.com/questions/49781884/microsoft-directx-sound-on-visual-studio-2017)
>Microsoft.DirectX.DirectSound is part of the legacy Managed DirectX 1.1 assemblies. They only supported for the .NET 1.1 and .NET 2.0 Runtimes and not the modern .NET 4.x Runtime. You also as you note have to force the use of /platform:x86.
>
>Your best option is to use SlimDX which is intended as a drop-in replacement for the Managed DirectX 1.1 assemblies including x64 support. A more modern solution is SharpDX, but of course you probably shouldn't be using DirectSound in a new app anyhow.

https://github.com/SlimDX/SlimDX-v2
