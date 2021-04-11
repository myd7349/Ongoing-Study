namespace MarshalCppClass
{
    using System;

    static class PersonNatives
    {
        public static string GetArch()
        {
            return IntPtr.Size == 8 ? PersonNativesX64.GetArch()
                : PersonNativesX86.GetArch();
        }

        public static IntPtr New(string name = "", int age = 0)
        {
            return IntPtr.Size == 8 ? PersonNativesX64.New(name, age)
                : PersonNativesX86.New(name, age);
        }

        public static void Delete(IntPtr person)
        {
            if (IntPtr.Size == 8)
                PersonNativesX64.Delete(person);
            else
                PersonNativesX86.Delete(person);
        }

        static public IntPtr GetName(IntPtr person)
        {
            return IntPtr.Size == 8 ? PersonNativesX64.GetName(person)
                : PersonNativesX86.GetName(person);
        }

        public static void SetName(IntPtr person, string name)
        {
            if (IntPtr.Size == 8)
                PersonNativesX64.SetName(person, name);
            else
                PersonNativesX86.SetName(person, name);
        }

        static public int GetAge(IntPtr person)
        {
            return IntPtr.Size == 8 ? PersonNativesX64.GetAge(person)
                : PersonNativesX86.GetAge(person);
        }

        public static void SetAge(IntPtr person, int age)
        {
            if (IntPtr.Size == 8)
                PersonNativesX64.SetAge(person, age);
            else
                PersonNativesX86.SetAge(person, age);
        }

        public static void Say(IntPtr person, string what)
        {
            if (IntPtr.Size == 8)
                PersonNativesX64.Say(person, what);
            else
                PersonNativesX86.Say(person, what);
        }
    }
}


// References:
// [Using a 32bit or 64bit dll in C# DllImport](https://stackoverflow.com/questions/10852634/using-a-32bit-or-64bit-dll-in-c-sharp-dllimport)
