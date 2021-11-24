namespace Common
{
    using System.IO;

    using Newtonsoft.Json;

    public static class JsonHelper
    {
        public static T Load<T>(string jsonFilePath) where T : new()
        {
            T instance = new T();

            if (File.Exists(jsonFilePath))
            {
                using (var reader = File.OpenText(jsonFilePath))
                using (var jsonReader = new JsonTextReader(reader))
                {
                    var jsonSerializer = new JsonSerializer();
                    instance = jsonSerializer.Deserialize<T>(jsonReader);
                }
            }

            return instance;
        }

        public static void Store<T>(string jsonFilePath, T instance)
        {
            var json = JsonConvert.SerializeObject(instance, Formatting.Indented);
            using (var writer = File.CreateText(jsonFilePath))
            {
                writer.Write(json);
            }
        }

#if false
        // Error:
        // Can not use it with FastReport.PictureObject objects.
        static string ObjectToJson<T>(T t)
        {
            return JsonConvert.SerializeObject(
                t,
                new JsonSerializerSettings
                {
                    Formatting = Formatting.Indented,
                    NullValueHandling = NullValueHandling.Ignore,
                    ReferenceLoopHandling = ReferenceLoopHandling.Ignore,
                });
        }
#endif
    }
}


#if false
namespace ObjectInspector
{
    using System;
    using System.Text.Json;
    using System.Text.Json.Serialization;

    static class JsonHelper
    {
        public static void PPrint<T>(T t)
        {
            string jsonString = JsonSerializer.Serialize(
                t,
                new JsonSerializerOptions
                {
                    WriteIndented = true,
                    ReferenceHandler = ReferenceHandler.Preserve,
                });
            Console.WriteLine(jsonString);
        }
    }
}
#endif


// References:
// [What is the best way to dump entire objects to a log in C#?](https://stackoverflow.com/questions/360277/what-is-the-best-way-to-dump-entire-objects-to-a-log-in-c)
// [C#: Printing all properties of an object](https://stackoverflow.com/questions/852181/c-printing-all-properties-of-an-object)
// [How to pretty print using System.Text.Json for unknown object](https://stackoverflow.com/questions/65620631/how-to-pretty-print-using-system-text-json-for-unknown-object)
// [How to serialize and deserialize (marshal and unmarshal) JSON in .NET](https://docs.microsoft.com/en-us/dotnet/standard/serialization/system-text-json-how-to?pivots=dotnet-6-0)
// [System.Text.Json Error Handling equivalency to Newtonsoft.Json (json.net) JsonSerializerSettings](https://stackoverflow.com/questions/66177062/system-text-json-error-handling-equivalency-to-newtonsoft-json-json-net-jsonse)
// [Handling reference loops in JSON.net](https://stackoverflow.com/questions/22297173/handling-reference-loops-in-json-net)
// [How to ignore a property in class if null, using json.net](https://stackoverflow.com/questions/6507889/how-to-ignore-a-property-in-class-if-null-using-json-net)
// [A way to pretty print a C# object](https://stackoverflow.com/questions/6309254/a-way-to-pretty-print-a-c-sharp-object)
