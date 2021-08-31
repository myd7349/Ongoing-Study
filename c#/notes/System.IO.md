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
