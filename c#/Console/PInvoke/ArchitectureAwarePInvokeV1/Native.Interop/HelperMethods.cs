namespace Native.Interop
{
    using System;

    internal static class HelperMethods
    {
        internal static string StringFormat(IFormatProvider provider, string format, params object[] args)
        {
            if (IsMono())
            {
                return string.Format(format, args);
            }

            return string.Format(provider, format, args);
        }

        private static bool IsMono()
        {
            try
            {
                lock (staticSyncRoot)
                {
                    if (!isMono.HasValue)
                    {
                        isMono = Type.GetType(MonoRuntimeType) != null;
                    }

                    return isMono.Value;
                }
            }
            catch
            {
            }

            return false;
        }

        internal static bool IsWindows()
        {
            PlatformID platform = Environment.OSVersion.Platform;
            if (platform != 0 && platform != PlatformID.Win32Windows && platform != PlatformID.Win32NT && platform != PlatformID.WinCE)
            {
                return false;
            }

            return true;
        }

        private static readonly object staticSyncRoot = new object();
        private static readonly string MonoRuntimeType = "Mono.Runtime";
        private static bool? isMono = null;
    }
}
