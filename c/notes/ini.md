- [winpr/ini.h](https://github.com/FreeRDP/FreeRDP/blob/master/winpr/include/winpr/ini.h), [winpr/ini.c](https://github.com/FreeRDP/FreeRDP/blob/master/winpr/libwinpr/utils/ini.c)
  - https://github.com/microsoft/wslg/blob/5e9419849c89863ad36753e7c1707f20f9e0d0cd/WSLGd/precomp.h#L30-L32
  
- [inih](https://github.com/benhoyt/inih)

- [inih](https://github.com/jtilly/inih)

- [simpleini](https://github.com/brofield/simpleini)

- [mINI](https://github.com/pulzed/mINI)

- https://github.com/dotnet/runtime/blob/1fa304a14a8be27428399bd6f2cc51736cb1515a/src/libraries/Microsoft.Extensions.Configuration.Ini/src/IniStreamConfigurationProvider.cs#L26-L81

  ```csharp
  public static IDictionary<string, string> Read(Stream stream)
  {
      var data = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
      using (var reader = new StreamReader(stream))
      {
          string sectionPrefix = string.Empty;
  
          while (reader.Peek() != -1)
          {
              string rawLine = reader.ReadLine();
              string line = rawLine.Trim();
  
              // Ignore blank lines
              if (string.IsNullOrWhiteSpace(line))
              {
                  continue;
              }
              // Ignore comments
              if (line[0] == ';' || line[0] == '#' || line[0] == '/')
              {
                  continue;
              }
              // [Section:header]
              if (line[0] == '[' && line[line.Length - 1] == ']')
              {
                  // remove the brackets
                  sectionPrefix = line.Substring(1, line.Length - 2) + ConfigurationPath.KeyDelimiter;
                  continue;
              }
  
              // key = value OR "value"
              int separator = line.IndexOf('=');
              if (separator < 0)
              {
                  throw new FormatException(SR.Format(SR.Error_UnrecognizedLineFormat, rawLine));
              }
  
              string key = sectionPrefix + line.Substring(0, separator).Trim();
              string value = line.Substring(separator + 1).Trim();
  
              // Remove quotes
              if (value.Length > 1 && value[0] == '"' && value[value.Length - 1] == '"')
              {
                  value = value.Substring(1, value.Length - 2);
              }
  
              if (data.ContainsKey(key))
              {
                  throw new FormatException(SR.Format(SR.Error_KeyIsDuplicated, key));
              }
  
              data[key] = value;
          }
      }
      return data;
  }
  ```

- [Doubt in reading numeric values from INI file](https://www.codeproject.com/Questions/242867/Doubt-in-INI-file-reading)

  ```c++
  long ReadIntegerValueFromIni( const CString& csAppName_i,
                                const CString& csKeyName_i,
                                const CString& csDefaultVal_i,
                                const CString& csFileName_i,
                                const int nMinVal_i,
                                const int nMaxVal_i )
  {
      long lKeyValue = 0;
      int nDefaultVal = _ttoi( csDefaultVal_i );
      try
      {
          const int SUCCESS_RET = 1;
          TCHAR tcszBuf[ MAX_PATH ];
          TCHAR tcszBufTemp[ MAX_PATH ];
          lKeyValue = nDefaultVal;
  
          // Read the value from INI file.
          GetPrivateProfileString( csAppName_i, csKeyName_i, csDefaultVal_i, tcszBuf, sizeof( tcszBuf ),
                                   csFileName_i );
          // Check whether the value read from ini is a valid numeric number or not.
          if( SUCCESS_RET != swscanf( tcszBuf, _T( "%d%s" ), &lKeyValue, &tcszBufTemp ))
          {
              lKeyValue = nDefaultVal;
              // Invalid value found so adjusted to Default Value.
          }
          // Check whether the value read from ini is within the allowed range or not.
          else if( nMinVal_i > lKeyValue || nMaxVal_i < lKeyValue )
          {
              lKeyValue = nDefaultVal;
              // Input value is not within the allowed range, so adjusted to Default Value
          }
          else
          {
              // Do nothing.
          }
      }
      catch( ... )
      {
          // Unhandled exception occured in ReadIntegerValueFromIni()
          lKeyValue = nDefaultVal;
      }
      return lKeyValue;
  }
  ```

- https://github.com/GothenburgBitFactory/libshared/blob/master/src/Configuration.h
