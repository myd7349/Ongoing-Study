namespace ProtectedModuleCannotDisassemble
{
    using static System.Console;

    class Program
    {
        static void Main(string[] args)
        {
            WriteLine("Hello, world!");
            ReadKey();
        }
    }
}


// References:
// [How to make .net library protected?](https://social.msdn.microsoft.com/Forums/vstudio/en-US/39a16240-129c-4abb-b2a9-c096d361c5f2/how-to-make-net-library-protected-?forum=netfxbcl)
// [Remove the ILDASM suppressildasmattribute limit](https://topic.alibabacloud.com/a/remove-the-ildasm-suppressildasmattribute-limit_8_8_31362126.html)
