// 2016-06-02T16:40+08:00
using Common;
using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace ECGLeads
{
    enum Lead
    {
        [Description("Lead I")]
        I,
        II,
        III,
        aVR,
        aVL,
        aVF,
        V1,
        V2,
        V3,
        V4,
        V5,
        V6,
    }

    static class LeadExtension
    {
        public static string Name(this Lead lead)
        {
            return Enum.GetName(typeof(Lead), lead);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Dictionary<Lead, string> leadNamesMap = new Dictionary<Lead, string>();

            var type = typeof(Lead);
            foreach (var value in Enum.GetValues(type))
                leadNamesMap[(Lead)value] = Enum.GetName(type, value);

            foreach (var kv in leadNamesMap)
                Console.WriteLine("{0,3}: {1:X}", kv.Value, (int)kv.Key);

            Console.WriteLine("{0} {1} {2}", (int)Lead.II, Lead.II, Lead.II.Name());
            Console.WriteLine("{0}", Lead.II.ToString());
            Console.WriteLine((Lead)1);

            foreach (var kv in Common.EnumHelper<Lead>.EnumValueToNameDict)
                Console.WriteLine("{0,2}: {1,3}", (int)kv.Key, kv.Value);

            var leadIDescription = Lead.I.GetDescription();
            Console.WriteLine(leadIDescription);
            Console.WriteLine(EnumHelper<Lead>.EnumDescriptionToValueDict[leadIDescription].ToString());

            Common.Util.Pause();
        }
    }
}

// References:
// [The Enumerable Enumerator](http://www.codeproject.com/Articles/16216/The-Enumerable-Enumerator)
