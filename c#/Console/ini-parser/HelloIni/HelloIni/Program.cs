namespace HelloIni
{
    using static System.Console;

    class Program
    {
        static void Main(string[] args)
        {
            using (var settings = new Settings("Settings.ini"))
            {
                WriteLine($"Server: {settings.Server}");
                WriteLine($"Port: {settings.Port}");
                WriteLine($"User: {settings.User}");

                settings.Port = settings.Port + 1;

                ReadKey();
            }
        }
    }
}
