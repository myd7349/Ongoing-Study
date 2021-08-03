namespace HelloIni
{
    using System;
    using System.Diagnostics;
    using System.IO;

    using IniParser;
    using IniParser.Model;

    class Settings : IDisposable
    {
        public Settings(string filePath)
        {
            Debug.Assert(!string.IsNullOrWhiteSpace(filePath));

            iniFilePath_ = filePath;
            iniParser_ = new FileIniDataParser();

            if (!Load())
                Reset();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        public string Server
        {
            get => iniData_["Account"]["Server"];
            set => iniData_["Account"]["Server"] = value;
        }

        public int Port
        {
            get
            {
                var portString = iniData_["Account"]["Port"];

                int port;
                if (!int.TryParse(portString, out port))
                    return PortDefault;

                return port;
            }

            set
            {
                iniData_["Account"]["Port"] = value.ToString();
            }
        }

        public string User
        {
            get => iniData_["Account"]["User"];
            set => iniData_["Account"]["User"] = value;
        }

        public bool Load()
        {
            if (!File.Exists(iniFilePath_))
                return false;

            iniData_ = iniParser_.ReadFile(iniFilePath_);
            return true;
        }

        public void Store()
        {
            iniParser_.WriteFile(iniFilePath_, iniData_);
        }

        public void Reset()
        {
            iniData_ = new IniData();
            iniData_["Account"]["Server"] = ServerDefault;
            iniData_["Account"]["Port"] = PortDefault.ToString();
            iniData_["Account"]["User"] = UserDefault;
        }

        private void Dispose(bool disposing)
        {
            if (disposed_)
                return;

            if (disposing)
            {
                Store();
            }

            disposed_ = true;
        }

        private const string ServerDefault = "localhost";
        private const int PortDefault = 80;
        private const string UserDefault = "admin";

        private string iniFilePath_;
        private FileIniDataParser iniParser_;
        private IniData iniData_;
        private bool disposed_ = false;
    }
}
