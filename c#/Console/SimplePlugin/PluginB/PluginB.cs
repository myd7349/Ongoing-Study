namespace PluginB
{

    using System;

    using PluginLib;

    public class PluginA : IPlugin
    {
        public string Name
        {
            get
            {
                return "PluginB";
            }
        }

        public void Do()
        {
            Console.WriteLine("Hi! This is plugin B.");
        }

        public bool Ok
        {
            get
            {
                return DateTime.Now.Second % 2 == 0;
            }
        }
    }
}
