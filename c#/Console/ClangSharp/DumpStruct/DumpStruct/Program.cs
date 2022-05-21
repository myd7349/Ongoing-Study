using System;
using System.Linq;

using ClangSharp;


namespace DumpStruct
{
    class Program
    {
        static void Main(string[] args)
        {
            var code = @"
struct edf_param_struct{         /* this structure contains all the relevant EDF-signal parameters of one signal */
  char   label[17];              /* label (name) of the signal, null-terminated string */
  long long smp_in_file;         /* number of samples of this signal in the file */
  double phys_max;               /* physical maximum, usually the maximum input of the ADC */
  double phys_min;               /* physical minimum, usually the minimum input of the ADC */
  int    dig_max;                /* digital maximum, usually the maximum output of the ADC, cannot not be higher than 32767 for EDF or 8388607 for BDF */
  int    dig_min;                /* digital minimum, usually the minimum output of the ADC, cannot not be lower than -32768 for EDF or -8388608 for BDF */
  int    smp_in_datarecord;      /* number of samples of this signal in a datarecord, if the datarecord has a duration of one second (default), then it equals the samplerate */
  char   physdimension[9];       /* physical dimension (uV, bpm, mA, etc.), null-terminated string */
  char   prefilter[81];          /* null-terminated string */
  char   transducer[81];         /* null-terminated string */
      };

typedef struct {
  void *handle;
} handle_t;

struct my_record {
  int a;
  char b;
  long c;
  char *d;
};
";

            var translationUnit = TranslationUnitHelper.CreateTranslationUnit(code);
            var recordDecls = translationUnit.TranslationUnitDecl.Decls.OfType<RecordDecl>().ToArray();
            foreach (var record in recordDecls)
                Console.WriteLine(record.Name);

            DumpStructLayout(translationUnit, "edf_param_struct");
            DumpStructLayout(translationUnit, "my_record");
        }

        static void DumpStructLayout(TranslationUnit translationUnit, string structName)
        {
            var recordDecls = translationUnit.TranslationUnitDecl.Decls.OfType<RecordDecl>().ToArray();

            Console.WriteLine("______________________________________________________________________________________");
            Console.WriteLine("|{0,-15}|{1,-20}|{2,-15}|{3,-15}|{4,-15}|",
                "Index", "Name", "Type", "SizeOf", "Alignment");

            var edfParamRecordDecl = recordDecls.First(decl => decl.Name == structName);
            foreach (var field in edfParamRecordDecl.Fields)
            {
                Console.WriteLine("|{0,-15}|{1,-20}|{2,-15}|{3,-15}|{4,-15}|",
                    field.FieldIndex,
                    field.Name,
                    field.Type,
                    field.Type.Handle.SizeOf,
                    field.Type.Handle.AlignOf);
            }
        }
    }
}


// References:
// https://github.com/dotnet/ClangSharp/blob/main/tests/ClangSharp.UnitTests/CursorTests/DeclTest.cs
// [WinApiMapper](https://github.com/OH1TR/WinApiMapper)
// https://www.nuget.org/packages/CppAst/
// https://stackoverflow.com/questions/19516075/how-do-i-use-clang-from-a-c-sharp-project
// https://stackoverflow.com/questions/47949969/llvm-get-the-offset-of-inside-struct
// https://stackoverflow.com/questions/2120367/c-sharp-command-to-get-struct-offset
// [How To: Best way to draw table in console app (C#)](https://stackoverflow.com/questions/856845/how-to-best-way-to-draw-table-in-console-app-c)
// [Packing not emitted for some structs](https://github.com/dotnet/ClangSharp/issues/233)
// https://github.com/dotnet/ClangSharp/blob/main/sources/ClangSharp.PInvokeGenerator/PInvokeGenerator.VisitDecl.cs
