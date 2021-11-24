namespace BaiduBOSDemo
{
    using System.IO;
    using System.Reflection;

    using Common;

    public struct Settings
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
        public long UploadPartSize { get; set; }
        public bool UseFileFullPathAsObjectKey { get; set; }
        public long DownloadSize { get; set; }

        public static Settings Load()
        {
            return JsonHelper.Load<Settings>(SettingsFilePath);
        }

        public static void Store(Settings settings)
        {
            JsonHelper.Store(SettingsFilePath, settings);
        }

        private const string SettingFileName = "BOSettings.json";
        private static readonly string SettingsFilePath;
    }
}
