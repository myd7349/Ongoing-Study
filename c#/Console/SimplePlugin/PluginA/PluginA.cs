namespace PluginA
{
    using System;

    using PluginLib;

    public class PluginA : IPlugin
    {
        public string Name
        {
            get
            {
                return "PluginA";
            }
        }

        public void Do()
        {
            Console.WriteLine("Hi! This is plugin A.");
        }

        public bool Ok
        {
            get
            {
                return DateTime.Now.Second % 2 != 0;
            }
        }
    }
}
