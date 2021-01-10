-1. [DirectSound Play Buffer Notify generating a notification based on WritePosition rather than PlayPosition](https://social.msdn.microsoft.com/Forums/en-US/f6c6f5cb-b766-407d-80f2-c5e9ccc4f899/directsound-play-buffer-notify-generating-a-notification-based-on-writeposition-rather-than)
>I think it is interesting to note that Microsoft has removed any mention of Managed DirectX in the Microsoft DirectX SDK (November 2007) release.  There is no longer a .chm file for managed code; there is no "managed" subdirectory under the "samples" directory and the sample explorer utility no longer has a "managed" check box for filtering.  Looks like its time to give up on C# for DirectX applications.


0. [Microsoft DirectX Sound on Visual Studio 2017](https://stackoverflow.com/questions/49781884/microsoft-directx-sound-on-visual-studio-2017)
>Microsoft.DirectX.DirectSound is part of the legacy Managed DirectX 1.1 assemblies. They only supported for the .NET 1.1 and .NET 2.0 Runtimes and not the modern .NET 4.x Runtime. You also as you note have to force the use of /platform:x86.
>
>Your best option is to use SlimDX which is intended as a drop-in replacement for the Managed DirectX 1.1 assemblies including x64 support. A more modern solution is SharpDX, but of course you probably shouldn't be using DirectSound in a new app anyhow.



1. To get Microsoft.DirectX.DirectSound installed on your PC, you need to download `DirectX End-User Runtimes (June 2010)` and install it.

2. [混合模式程序集是针对“v1.1.4322”版的运行时生成的](https://blog.csdn.net/yybj/article/details/38312269)
App.config
```xml
<?xml version="1.0"?>
<configuration>
  <startup useLegacyV2RuntimeActivationPolicy="true">
    <supportedRuntime version="v4.0"/>
  </startup>
</configuration>
```

[What does 'useLegacyV2RuntimeActivationPolicy' do in the .NET 4 config?](https://stackoverflow.com/questions/1604663/what-does-uselegacyv2runtimeactivationpolicy-do-in-the-net-4-config/2467255#2467255)

[正尝试在 OS 加载程序锁内执行托管代码。不要尝试在 DllMain 或映像初始化函数内运行托管代码，这样做会导致应用程序挂起。](https://blog.csdn.net/aoshilang2249/article/details/38067217)
