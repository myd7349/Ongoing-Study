<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.Globalization.dll</Reference>
  <Namespace>System.Globalization</Namespace>
</Query>

static int Main(string[] argv)
{
    CultureInfo ci = CultureInfo.InstalledUICulture;

    Console.WriteLine("Default Language Info:" );
    Console.WriteLine("* Name: {0}"                    , ci.Name );
    Console.WriteLine("* Display Name: {0}"            , ci.DisplayName );
    Console.WriteLine("* English Name: {0}"            , ci.EnglishName );
    Console.WriteLine("* 2-letter ISO Name: {0}"       , ci.TwoLetterISOLanguageName );
    Console.WriteLine("* 3-letter ISO Name: {0}"       , ci.ThreeLetterISOLanguageName );
    Console.WriteLine("* 3-letter Win32 API Name: {0}" , ci.ThreeLetterWindowsLanguageName );

    return 0;
}

// References:
// https://stackoverflow.com/questions/5710127/get-operating-system-language-in-c-sharp
