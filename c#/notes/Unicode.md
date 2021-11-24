1. [Effective way to find any file's Encoding](https://stackoverflow.com/questions/3825390/effective-way-to-find-any-files-encoding)

   > ```csharp
   > /// <summary>
   > /// Determines a text file's encoding by analyzing its byte order mark (BOM).
   > /// Defaults to ASCII when detection of the text file's endianness fails.
   > /// </summary>
   > /// <param name="filename">The text file to analyze.</param>
   > /// <returns>The detected encoding.</returns>
   > public static Encoding GetEncoding(string filename)
   > {
   >     // Read the BOM
   >     var bom = new byte[4];
   >     using (var file = new FileStream(filename, FileMode.Open, FileAccess.Read))
   >     {
   >         file.Read(bom, 0, 4);
   >     }
   > 
   >     // Analyze the BOM
   >     if (bom[0] == 0x2b && bom[1] == 0x2f && bom[2] == 0x76) return Encoding.UTF7;
   >     if (bom[0] == 0xef && bom[1] == 0xbb && bom[2] == 0xbf) return Encoding.UTF8;
   >     if (bom[0] == 0xff && bom[1] == 0xfe && bom[2] == 0 && bom[3] == 0) return Encoding.UTF32; //UTF-32LE
   >     if (bom[0] == 0xff && bom[1] == 0xfe) return Encoding.Unicode; //UTF-16LE
   >     if (bom[0] == 0xfe && bom[1] == 0xff) return Encoding.BigEndianUnicode; //UTF-16BE
   >     if (bom[0] == 0 && bom[1] == 0 && bom[2] == 0xfe && bom[3] == 0xff) return new UTF32Encoding(true, true);  //UTF-32BE
   > 
   >     // We actually have no idea what the encoding is if we reach this point, so
   >     // you may wish to return null instead of defaulting to ASCII
   >     return Encoding.ASCII;
   > }
   > ```

2. https://github.com/CharsetDetector/UTF-unknown

3. [How to Get a File's Encoding with C#](https://www.codeproject.com/Tips/1231324/How-to-Get-a-Files-Encoding-with-Csharp)

   > ```csharp
   > /// <summary
   > /// Get File's Encoding
   > /// </summary>
   > /// <param name="filename">The path to the file
   > private static Encoding GetEncoding(string filename)
   > {
   >     // This is a direct quote from MSDN:  
   >     // The CurrentEncoding value can be different after the first
   >     // call to any Read method of StreamReader, since encoding
   >     // autodetection is not done until the first call to a Read method.
   > 
   >     using (var reader = new StreamReader(filename, Encoding.Default, true))
   >     {
   >         if (reader.Peek() >= 0) // you need this!
   >             reader.Read();
   > 
   >         return reader.CurrentEncoding;
   >     }
   > }
   > ```



