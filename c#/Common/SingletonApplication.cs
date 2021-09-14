// 2018-07-21T14:05+08:00
// This is just a simple implementation of [0].
// For a more powerful one, please refer to [1].
namespace Common
{
    using System;
    using System.Threading;

    public class SingletonApplication : IDisposable
    {
        public SingletonApplication(string name, bool global = false)
        {
            if (global)
                name = "Global\\" + name;

            bool createdNew;
            mutex = new Mutex(false, name, out createdNew);
            IsAlreadyRunning = !createdNew;
        }

        public bool IsAlreadyRunning
        {
            get;
            private set;
        }

        public void Dispose()
        {
            mutex.Dispose();
        }

        private Mutex mutex;
    }
}

// References:
// [0] C# 6.0 in a Nutshell, P912
// [1] https://www.codeproject.com/articles/4430/single-instance-application-in-c
// [2] http://www.cnblogs.com/dc10101/archive/2009/11/24/1609146.html
// [Restore application from system tray when clicking on desktop shortcut](https://stackoverflow.com/questions/10529370/restore-application-from-system-tray-when-clicking-on-desktop-shortcut)
//     > GC.KeepAlive(mutex);
