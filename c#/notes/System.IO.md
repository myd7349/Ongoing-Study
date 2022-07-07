https://stackoverflow.com/questions/35909877/c-sharp-binarywriter-and-endianness
> BinaryWriter stores this data type in little endian format.

https://stackoverflow.com/questions/9759697/reading-a-file-used-by-another-process

[Creating sine or square wave in C#](https://stackoverflow.com/questions/203890/creating-sine-or-square-wave-in-c-sharp)

[What's the fastest way to read a text file line-by-line?](https://stackoverflow.com/questions/8037070/whats-the-fastest-way-to-read-a-text-file-line-by-line)

> ```cs
> const Int32 BufferSize = 128;
> using (var fileStream = File.OpenRead(fileName))
> using (var streamReader = new StreamReader(fileStream, Encoding.UTF8, true, BufferSize)) {
>     String line;
>     while ((line = streamReader.ReadLine()) != null)
>       // Process line
> }
> ```

[How to read a text file one line at a time (C# Programming Guide)](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/file-system/how-to-read-a-text-file-one-line-at-a-time)

> ```csharp
> int counter = 0;  
> string line;  
>   
> // Read the file and display it line by line.  
> System.IO.StreamReader file =
>     new System.IO.StreamReader(@"c:\test.txt");  
> while((line = file.ReadLine()) != null)  
> {  
>     System.Console.WriteLine(line);  
>     counter++;  
> }  
>   
> file.Close();  
> System.Console.WriteLine("There were {0} lines.", counter);  
> // Suspend the screen.  
> System.Console.ReadLine();  
> ```

https://github.com/dotnet/runtime/blob/1fa304a14a8be27428399bd6f2cc51736cb1515a/src/libraries/Microsoft.Extensions.Configuration/tests/Common/TestStreamHelpers.cs#L108-L117

> ```csharp
> public static Stream StringToStream(string str)
> {
>     var memStream = new MemoryStream();
>     var textWriter = new StreamWriter(memStream);
>     textWriter.Write(str);
>     textWriter.Flush();
>     memStream.Seek(0, SeekOrigin.Begin);
> 
>     return memStream;
> }
> ```

https://github.com/dahall/Vanara/blob/56cda5a8f4d6648563651996d99f471f9e49e56f/Core/Extensions/InteropExtensions.cs#L1047-L1068

[How can I create a temp file with a specific extension with .NET?](https://stackoverflow.com/questions/581570/how-can-i-create-a-temp-file-with-a-specific-extension-with-net)

MemoryMapFile:

- https://github.com/microsoft/perfview/blob/7bc1b55ebf6773f8afcdf46a96d2e9ccc763aeee/src/FastSerialization/MemoryMappedFileStreamWriter.cs

https://github.com/microsoft/perfview/blob/7bc1b55ebf6773f8afcdf46a96d2e9ccc763aeee/src/FastSerialization/CompressedStream.cs

[File IO improvements in .NET 6](https://devblogs.microsoft.com/dotnet/file-io-improvements-in-dotnet-6/)

https://github.com/fo-dicom/fo-dicom/blob/development/DICOM/IO/Buffer/TempFileBuffer.cs

https://github.com/fo-dicom/fo-dicom/blob/development/DICOM/IO/TemporaryFile.cs

[How do I check if a given string is a legal/valid file name under Windows?](https://stackoverflow.com/questions/62771/how-do-i-check-if-a-given-string-is-a-legal-valid-file-name-under-windows)

> You can get a list of invalid characters from [`Path.GetInvalidPathChars`](http://msdn.microsoft.com/en-us/library/system.io.path.getinvalidpathchars.aspx) and [`GetInvalidFileNameChars`](http://msdn.microsoft.com/en-us/library/system.io.path.getinvalidfilenamechars.aspx).

[C# delete a folder and all files and folders within that folder](https://stackoverflow.com/questions/2222718/c-sharp-delete-a-folder-and-all-files-and-folders-within-that-folder)

```csharp
dir.Delete(true); // true => recursive delete
```

File.ReadLines vs File.ReadAllLines

Path.GetTempFileName

```csharp
// Create a temporary file on disk.
string tempFile = Path.GetTempFileName();

// Write random data to the temporary file.
using (var fileStream = File.OpenWrite(tempFile))
{
   Random rand = new Random();
   byte[] buffer = new byte[1024];
   for (int i = 0; i < 512; i++)
   {
      rand.NextBytes(buffer);
      fileStream.Write(buffer, 0, buffer.Length);
   }
}
```

[Can you call Directory.GetFiles() with multiple filters?](https://stackoverflow.com/questions/163162/can-you-call-directory-getfiles-with-multiple-filters)

[How to get relative path from absolute path](https://stackoverflow.com/questions/275689/how-to-get-relative-path-from-absolute-path)

[c# open file with default application and parameters](https://stackoverflow.com/questions/11365984/c-sharp-open-file-with-default-application-and-parameters)

[Get the (last part of) current directory name in C#](https://stackoverflow.com/questions/6018293/get-the-last-part-of-current-directory-name-in-c-sharp)

```csharp
Console.WriteLine(Path.GetDirectoryName(@"D:\1\2\3"));
Console.WriteLine(Path.GetDirectoryName(@"D:\1\2\3\"));

Console.WriteLine(Path.GetFileName(@"D:\1\2\3"));
Console.WriteLine(Path.GetFileName(@"D:\1\2\3\"));

Console.WriteLine(GetBaseName(@"D:\1\2\3"));
Console.WriteLine(GetBaseName(@"D:\1\2\3\"));

Console.WriteLine(GetBaseNameV2(@"D:\1\2\3"));
Console.WriteLine(GetBaseNameV2(@"D:\1\2\3\"));

static string GetBaseName(string path)
{
    if (path == null)
        throw new ArgumentNullException(nameof(path));

    path = path.TrimEnd(Path.DirectorySeparatorChar)
        .TrimEnd(Path.AltDirectorySeparatorChar);
    return Path.GetFileName(path);
}

static string GetBaseNameV2(string path)
{
    if (path == null)
        throw new ArgumentNullException(nameof(path));

    return new DirectoryInfo(path).Name;
}


// References:
// [Get the (last part of) current directory name in C#](https://stackoverflow.com/questions/6018293/get-the-last-part-of-current-directory-name-in-c-sharp)
```

[Verifying path equality with .Net](https://stackoverflow.com/questions/7344978/verifying-path-equality-with-net)

[Best way to determine if two path reference to same file in C#](https://stackoverflow.com/questions/410705/best-way-to-determine-if-two-path-reference-to-same-file-in-c-sharp)

[Detect if two paths are the same](https://stackoverflow.com/questions/31097236/detect-if-two-paths-are-the-same)

> Path.GetRandomFileName

[How to determine if two directory pathnames resolve to the same target](https://superuser.com/questions/881547/how-to-determine-if-two-directory-pathnames-resolve-to-the-same-target)

Stream

[NetworkStream Class](https://learn.microsoft.com/en-us/dotnet/api/system.net.sockets.networkstream?view=net-6.0)

> The NetworkStream does not support random access to the network data stream. The value of the CanSeek property, which indicates whether the stream supports seeking, is always false; reading the Position property, reading the Length property, or calling the Seek method will throw a NotSupportedException.
