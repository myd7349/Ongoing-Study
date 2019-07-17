// 2018-05-17T12:14+08:00
namespace MyLib
{
    using System.Runtime.InteropServices;

    using MyLibBase;

    public static unsafe class NativeLib
    {
        [DllImport("NativeLib.dll")]
        public static extern string GetName();
    }

    public sealed class MyLibWithPInvoke : MyLibBase
    {
        public MyLibWithPInvoke(string message)
        {
            message_ = message;
        }

        public override string Message => message_;

        public override string Name => NativeLib.GetName();

        private readonly string message_;
    }
}
