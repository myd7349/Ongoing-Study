namespace Common
{
    using System;
    using System.Diagnostics;
    using System.IO;
    using System.Text;

    using Newtonsoft.Json;
    using Newtonsoft.Json.Bson;

    public static class JsonHelper
    {
        public static T Load<T>(string jsonFilePath)
        {
            T instance = default(T);

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

        public static string LoadJson(string filePath)
        {
            return File.ReadAllText(filePath);
        }

        public static string LoadJson(string filePath, bool? indented = null)
        {
            using (var fileStream = File.OpenText(filePath))
            using (var jsonTextReader = new JsonTextReader(fileStream))
            {
                var stringBuilder = new StringBuilder();
                using (var stringWriter = new StringWriter(stringBuilder))
                using (var jsonTextWriter = new JsonTextWriter(stringWriter))
                {
                    if (indented == true)
                        jsonTextWriter.Formatting = Formatting.Indented;
                    else if (indented == false)
                        jsonTextWriter.Formatting = Formatting.None;

                    jsonTextWriter.WriteToken(jsonTextReader);
                }

                return stringBuilder.ToString();
            }
        }

        public static string FormatJson(string json, bool indented = true)
        {
            using (var textReader = new StringReader(json))
            using (var jsonTextReader = new JsonTextReader(textReader))
            {
                var stringBuilder = new StringBuilder();
                using (var stringWriter = new StringWriter(stringBuilder))
                using (var jsonTextWriter = new JsonTextWriter(stringWriter))
                {
                    if (indented)
                        jsonTextWriter.Formatting = Formatting.Indented;
                    else
                        jsonTextWriter.Formatting = Formatting.None;

                    jsonTextWriter.WriteToken(jsonTextReader);
                }

                return stringBuilder.ToString();
            }
        }

        public static void StoreJson(string jsonFilePath, string json, bool? indented = null)
        {
            if (string.IsNullOrEmpty(json))
                json = "{}";

            if (indented == null)
                File.WriteAllText(jsonFilePath, json);
            else
                File.WriteAllText(jsonFilePath, FormatJson(json, indented.Value));
        }

        public static void Store<T>(string jsonFilePath, T instance, bool indented = true)
        {
            var json = JsonConvert.SerializeObject(instance, indented ? Formatting.Indented : Formatting.None);
            using (var writer = File.CreateText(jsonFilePath))
            {
                writer.Write(json);
            }
        }

        public static T LoadBson<T>(string bsonFilePath)
        {
            T instance = default(T);

            if (File.Exists(bsonFilePath))
            {
                using (var fileStream = File.Open(bsonFilePath, FileMode.Open))
                using (var bsonReader = new BsonDataReader(fileStream))
                {
                    var jsonSerializer = new JsonSerializer();
                    instance = jsonSerializer.Deserialize<T>(bsonReader);
                }
            }

            return instance;
        }

        public static string LoadBson(string filePath, bool? indented = null)
        {
            using (var fileStream = File.OpenRead(filePath))
            using (var bsonReader = new BsonDataReader(fileStream))
            {
                var stringBuilder = new StringBuilder();
                using (var stringWriter = new StringWriter(stringBuilder))
                using (var jsonTextWriter = new JsonTextWriter(stringWriter))
                {
                    if (indented == true)
                        jsonTextWriter.Formatting = Formatting.Indented;
                    else if (indented == false)
                        jsonTextWriter.Formatting = Formatting.None;

                    jsonTextWriter.WriteToken(bsonReader);
                }

                return stringBuilder.ToString();
            }
        }

        public static void StoreBson<T>(string bsonFilePath, T instance)
        {
            using (var fileStream = File.OpenWrite(bsonFilePath))
            using (var bsonWriter = new BsonDataWriter(fileStream))
            {
                var serializer = new JsonSerializer();
                serializer.Serialize(bsonWriter, instance);
            }
        }

        public static void StoreBson(string bsonFilePath, string json)
        {
#if false
            using (var fileStream = File.OpenWrite(bsonFilePath))
            using (var bsonWriter = new BsonDataWriter(fileStream))
            {
                bsonWriter.WriteRaw(json);
            }
#else
            if (string.IsNullOrEmpty(json))
                json = null;

            using (var textReader = new StringReader(json))
            using (var jsonTextReader = new JsonTextReader(textReader))
            {
                var jsonSerializer = new JsonSerializer();
                var instance = jsonSerializer.Deserialize(jsonTextReader);

                using (var fileStream = File.OpenWrite(bsonFilePath))
                using (var bsonWriter = new BsonDataWriter(fileStream))
                {
                    jsonSerializer.Serialize(bsonWriter, instance);
                }
            }
#endif
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

        public static T DeepClone<T>(T source) where T : class
        {
            if (source == null)
                throw new ArgumentNullException(nameof(source));

            var json = JsonConvert.SerializeObject(source);

            // initialize inner objects individually
            // for example in default constructor some list property initialized with some values,
            // but in 'source' these items are cleaned -
            // without ObjectCreationHandling.Replace default constructor values will be added to result
            var deserializeSettings = new JsonSerializerSettings
            {
                ObjectCreationHandling = ObjectCreationHandling.Replace
            };

            return JsonConvert.DeserializeObject<T>(json, deserializeSettings);
        }

        public static void PopulateWith<T>(this T target, T source) where T : class
        {
            if (target == null)
                throw new ArgumentNullException(nameof(target));

            if (source == null)
                throw new ArgumentNullException(nameof(source));

            Debug.Assert(!ReferenceEquals(target, source));
            if (ReferenceEquals(target, source))
                return;

            var json = JsonConvert.SerializeObject(source);

            JsonConvert.PopulateObject(json, target);
        }
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
// [Serialize to BSON](https://www.newtonsoft.com/json/help/html/SerializeToBson.htm)
// [Deserialize from BSON](https://www.newtonsoft.com/json/help/html/DeserializeFromBson.htm)
// [How to convert JSON to BSON using Json.NET](https://stackoverflow.com/questions/33685505/how-to-convert-json-to-bson-using-json-net)
// [BsonToJson.cs](https://gist.github.com/davideicardi/e001ce88663bb6ef1d9d04f96f8b16c6)
// [merge-json.cs](https://gist.github.com/gordonglas/6c9ddff073291f8aa90b842caad97154)
// [What is the easiest way to convert JSON into BSON in .net world](https://stackoverflow.com/questions/27012987/what-is-the-easiest-way-to-convert-json-into-bson-in-net-world)
// [What is the minimum valid JSON?](https://stackoverflow.com/questions/18419428/what-is-the-minimum-valid-json)
// [Is null valid JSON (4 bytes, nothing else)](https://stackoverflow.com/questions/8526995/is-null-valid-json-4-bytes-nothing-else)
// https://github.com/mathiasbynens/small/issues/22
// [Deep cloning objects](https://stackoverflow.com/questions/78536/deep-cloning-objects)
// [Overlay data from JSON string to existing object instance](https://stackoverflow.com/questions/5157079/overlay-data-from-json-string-to-existing-object-instance)
