namespace UnsuppressIldasmAttribute
{
    using static System.Console;
    using static System.IO.Path;
    using static System.Reflection.Assembly;

    using Mono.Cecil;

    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 2)
            {
                PrintHelp();
                return;
            }

            RemoveSuppressIldasmAttribute(args[0], args[1]);
        }

        static void PrintHelp()
        {
            var programName = GetFileNameWithoutExtension(GetEntryAssembly().Location);
            WriteLine($"{programName} - Remove SuppressIldasmAttribute from input assembly file.");
            WriteLine("Usage:\n\t{programName} <input> <output>");
        }

        static void RemoveSuppressIldasmAttribute(string input, string output)
        {
            AssemblyDefinition assembly = AssemblyDefinition.ReadAssembly(input);
            foreach (CustomAttribute attribute in assembly.CustomAttributes)
            {
                if (attribute.Constructor.DeclaringType.Name == "SuppressIldasmAttribute")
                {
                    assembly.CustomAttributes.Remove(attribute);
                    break;
                }
            }

            assembly.Name.PublicKey = null;
            assembly.Name.PublicKeyToken = null;
            assembly.Write(output);
        }
    }
}


// References:
// [How to make .net library protected?](https://social.msdn.microsoft.com/Forums/vstudio/en-US/39a16240-129c-4abb-b2a9-c096d361c5f2/how-to-make-net-library-protected-?forum=netfxbcl)
// [Remove the ILDASM suppressildasmattribute limit](https://topic.alibabacloud.com/a/remove-the-ildasm-suppressildasmattribute-limit_8_8_31362126.html)
