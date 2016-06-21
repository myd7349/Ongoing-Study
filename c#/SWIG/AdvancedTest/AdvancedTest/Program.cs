// 2016-06-21T14:36+08:00
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

            // 

            Util.Pause();
        }
    }
}
