namespace Common
{
    // coreclr\src\mscorlib\src\System\Numerics\Hashing\HashHelpers.cs
    public static class HashHelpers
    {
        public static int CombineHash(int h1, int h2)
        {
            unchecked
            {
                // RyuJIT optimizes this to use the ROL instruction
                // Related GitHub pull request: dotnet/coreclr#1830
                uint rol5 = ((uint)h1 << 5) | ((uint)h1 >> 27);
                return ((int)rol5 + h1) ^ h2;
            }
        }
    }
}


// References:
// https://docs.microsoft.com/en-us/dotnet/api/system.runtime.compilerservices.runtimehelpers.gethashcode?view=net-5.0
// https://github.com/commandlineparser/commandline/blob/master/src/CommandLine/Infrastructure/ReferenceEqualityComparer.cs
