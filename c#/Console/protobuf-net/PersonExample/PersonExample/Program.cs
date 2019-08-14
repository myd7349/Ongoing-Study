namespace PersonExample
{
    using static System.Console;
    using System.IO;

    using ProtoBuf;

    class Program
    {
        static void Main(string[] args)
        {
            var person1 = new PersonV1.Person
            {
                Id = 123,
                Name = "John",
                Email = "john@protonmail.com",
                Address = "Matrix",
            };

            person1.Phones.Add(
                new PersonV1.Person.PhoneNumber
                {
                    Number = "010-123456",
                    Type = PersonV1.Person.PhoneType.Home
                }
                );
            person1.Phones.Add(
                new PersonV1.Person.PhoneNumber
                {
                    Number = "010-012345",
                    Type = PersonV1.Person.PhoneType.Work
                }
                );
            person1.Phones.Add(
                new PersonV1.Person.PhoneNumber
                {
                    Number = "123456789",
                    Type = PersonV1.Person.PhoneType.Mobile
                }
                );

            using (var file = File.Create("person.bin"))
                Serializer.Serialize(file, person1);

            PersonV2.Person person2;
            using (var file = File.OpenRead("person.bin"))
                person2 = Serializer.Deserialize<PersonV2.Person>(file);

            WriteLine("Name: {0}", person2.Name);
            WriteLine("Id: {0}", person2.Id);
            WriteLine("Email: {0}", person2.Email);

            foreach (var phone in person2.Phones)
                WriteLine("Phone: Type: {0}, Number: {1}", phone.Type, phone.Number);

            ReadKey();
        }
    }
}


// References:
// https://github.com/protobuf-net/protobuf-net
// http://www.ben-morris.com/protocol-buffers-protobuf-net-vs-protobuf-csharp-port/
// https://stackoverflow.com/questions/38654856/how-to-install-protobuf-net-on-visual-studio-2012-using-nuget
