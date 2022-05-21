using System;
using System.Text;

using ClangSharp;
using ClangSharp.Interop;

namespace DumpStruct
{
    public static class TranslationUnitHelper
    {
        private const string DefaultInputFileName = "ClangUnsavedFile.h";

        private const CXTranslationUnit_Flags DefaultTranslationUnitFlags = CXTranslationUnit_Flags.CXTranslationUnit_IncludeAttributedTypes      // Include attributed types in CXType
                                                                            | CXTranslationUnit_Flags.CXTranslationUnit_VisitImplicitAttributes;    // Implicit attributes should be visited

        private static readonly string[] DefaultClangCommandLineArgs = new string[]
        {
            "-std=c++17",                           // The input files should be compiled for C++ 17
            "-xc++",                                // The input files are C++
            "-Wno-pragma-once-outside-header"       // We are processing files which may be header files
        };

        public static TranslationUnit CreateTranslationUnit(string inputContents)
        {
            using (var unsavedFile = CXUnsavedFile.Create(DefaultInputFileName, inputContents))
            {
                var unsavedFiles = new CXUnsavedFile[] { unsavedFile };

                var index = CXIndex.Create();
                var translationUnit = CXTranslationUnit.Parse(index, DefaultInputFileName, DefaultClangCommandLineArgs, unsavedFiles, DefaultTranslationUnitFlags);

                if (translationUnit.NumDiagnostics != 0)
                {
                    var errorDiagnostics = new StringBuilder();
                    _ = errorDiagnostics.AppendLine($"The provided {nameof(CXTranslationUnit)} has the following diagnostics which prevent its use:");
                    var invalidTranslationUnitHandle = false;

                    for (uint i = 0; i < translationUnit.NumDiagnostics; ++i)
                    {
                        using (var diagnostic = translationUnit.GetDiagnostic(i))
                        {
                            if (diagnostic.Severity == CXDiagnosticSeverity.CXDiagnostic_Error ||
                                diagnostic.Severity == CXDiagnosticSeverity.CXDiagnostic_Fatal)
                            {
                                invalidTranslationUnitHandle = true;
                                _ = errorDiagnostics.Append(' ', 4);
                                _ = errorDiagnostics.AppendLine(diagnostic.Format(CXDiagnosticDisplayOptions.CXDiagnostic_DisplayOption).ToString());
                            }
                        }
                    }

                    if (invalidTranslationUnitHandle)
                        throw new Exception(errorDiagnostics.ToString());
                }

                return TranslationUnit.GetOrCreate(translationUnit);
            }
        }
    }
}


// References:
// https://github.com/dotnet/ClangSharp/blob/main/tests/ClangSharp.UnitTests/TranslationUnitTest.cs
// https://www.nuget.org/packages/ClangSharp#usedby-body-tab
