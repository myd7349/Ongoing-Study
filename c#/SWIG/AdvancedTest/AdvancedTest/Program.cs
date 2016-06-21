// 2016-06-21T14:36+08:00
using System.Diagnostics;

using Common;

namespace AdvancedTest
{
    class Program
    {
        static void Main(string[] args)
        {
            // Windows Integral Types Test
            TestSuite.ToBeOrNotToBe(1);

            // Class Type As Argument.
            Person person = new Person();

            Message message = new Message();
            message.message = "Hello";

            person.Say(message);
            person.Say("world");

            // Copy Boolean Array
            bool[] source = { true, true, false, true, true, false, true };
            bool[] target = new bool[source.Length];

            TestSuite.CopyBooleanArray(source, target, source.Length);
            Debug.Assert(target.EqualTo(source));

            Util.Pause();
        }
    }
}
