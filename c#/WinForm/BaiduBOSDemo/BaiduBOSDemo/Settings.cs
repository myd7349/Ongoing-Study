namespace BaiduBOSDemo
{
    using System.IO;
    using System.Reflection;

    using Newtonsoft.Json;

    struct Settings
    {
        static Settings()
        {
            var appPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            SettingsFilePath = Path.Combine(appPath, SettingFileName);
        }

        public string AccessKey { get; set; }
        public string SecretAccessKey { get; set; }
        public string EndPoint { get; set; }
        public string CurrentBucket { get; set; }

        public static Settings Load()
        {
            Settings settings = new Settings();

            if (File.Exists(SettingsFilePath))
            {
                using (var reader = File.OpenText(SettingsFilePath))
                using (var jsonReader = new JsonTextReader(reader))
                {
                    var jsonSerializer = new JsonSerializer();
                    settings = jsonSerializer.Deserialize<Settings>(jsonReader);
                }
            }

            return settings;
        }

        public static void Store(Settings settings)
        {
            var json = JsonConvert.SerializeObject(settings, Formatting.Indented);
            using (var writer = File.CreateText(SettingsFilePath))
            {
                writer.Write(json);
            }
        }

        private const string SettingFileName = "BOSettings.json";
        private static readonly string SettingsFilePath;
    }
}
