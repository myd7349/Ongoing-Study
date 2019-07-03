namespace PluginLib
{
    public interface IPlugin
    {
        string Name { get; }
        void Do();
        bool Ok { get; }
    }
}


// References:
// https://www.codeproject.com/articles/889453/load-and-unload-plug-in-without-file-lock
// https://code.msdn.microsoft.com/windowsdesktop/Creating-a-simple-plugin-b6174b62
