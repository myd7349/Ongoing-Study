namespace Common
{
    using System.Diagnostics;
    using System.Runtime.CompilerServices;

    public static class DiagnosticsHelper
    {
        [MethodImpl(MethodImplOptions.NoInlining)]
        public static string GetCurrentMethodName()
        {
            var stackTrace = new StackTrace();
            var stackFrame = stackTrace.GetFrame(1);

            return stackFrame.GetMethod().Name;
        }
    }
}


// References:
// [How to get the name of the current method from code](https://stackoverflow.com/questions/2652460/how-to-get-the-name-of-the-current-method-from-code)
// [Can you use reflection to find the name of the currently executing method?](https://stackoverflow.com/questions/44153/can-you-use-reflection-to-find-the-name-of-the-currently-executing-method)
