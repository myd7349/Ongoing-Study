namespace BaiduBOSDemo
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
    }
}
