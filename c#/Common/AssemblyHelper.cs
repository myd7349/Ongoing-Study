﻿namespace Common
{
    using System;
    using System.Reflection;

    public static class AssemblyHelper
    {
        public static string GetBuildVersion(this Assembly assembly)
        {
            if (assembly == null)
                throw new ArgumentNullException("assembly");

            var assemblyInformationalVersionAttributes = assembly
                .GetCustomAttributes(typeof(AssemblyInformationalVersionAttribute), false)
                as AssemblyInformationalVersionAttribute[];
            if (assemblyInformationalVersionAttributes != null && assemblyInformationalVersionAttributes.Length > 0)
                return assemblyInformationalVersionAttributes[0].InformationalVersion;

            return string.Empty;
        }
    }
}


// References:
// https://github.com/mattleibow/SkiaSharpFiddle/blob/master/SkiaSharpFiddle/ViewModels/MainViewModel.cs
// https://github.com/PixiEditor/PixiEditor/blob/master/src/PixiEditor/Helpers/VersionHelpers.cs
