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