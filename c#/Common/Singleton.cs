using System;
using System.Reflection;

namespace Common
{
#if true
    public sealed class Singleton<T> where T : new()
    {
        private static readonly Lazy<T> lazy = new Lazy<T>(() => new T());

        public static T Instance => lazy.Value;

        private Singleton()
        {
        }
    }
#else
    public abstract class Singleton<T> where T : Singleton<T>
    {
        private static T Create()
        {
            var constructor = typeof(T).GetConstructor(BindingFlags.NonPublic | BindingFlags.Instance, null, new Type[0], null);
            return (T)constructor.Invoke(null);
        }

        private static T instance_ = null;
        private static readonly object lock_ = new object();

        public static T Instance
        {
            get
            {
                if (instance_ == null)
                {
                    lock (lock_)
                    {
                        if (instance_ == null)
                            instance_ = Create();
                    }
                }

                return instance_;
            }
        }

        private Singleton()
        {
        }
    }
#endif
}


// References:
// [Thread Safe C# Singleton Pattern](https://stackoverflow.com/questions/12316406/thread-safe-c-sharp-singleton-pattern)
// [Implementing the Singleton Pattern in C#](https://csharpindepth.com/Articles/Singleton)
// [Accessing a Private Constructor from Outside the Class in C#](https://stackoverflow.com/questions/4162776/accessing-a-private-constructor-from-outside-the-class-in-c-sharp)
