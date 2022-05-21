[Is there any generic Parse() function that will convert a string to any type using parse?](https://stackoverflow.com/questions/3502493/is-there-any-generic-parse-function-that-will-convert-a-string-to-any-type-usi)

[How to make a Generic Type Cast function](https://stackoverflow.com/questions/6884653/how-to-make-a-generic-type-cast-function)

https://github.com/shadowsocks/shadowsocks-windows/blob/main/Shadowsocks/Utilities/Base64Url.cs

Convert.ToInt32

```csharp
Console.WriteLine(Convert.ToInt32(1.1)); // 1
Console.WriteLine(Convert.ToInt32(1.6)); // 2
```

https://github.com/dotnet/runtime/blob/main/src/libraries/System.Private.CoreLib/src/System/Convert.cs

```csharp
public static int ToInt32(float value)
{
    return ToInt32((double)value);
}

public static int ToInt32(double value)
{
    if (value >= 0)
    {
        if (value < 2147483647.5)
        {
            int result = (int)value;
            double dif = value - result;
            if (dif > 0.5 || dif == 0.5 && (result & 1) != 0) result++;
            return result;
        }
    }
    else
    {
        if (value >= -2147483648.5)
        {
            int result = (int)value;
            double dif = value - result;
            if (dif < -0.5 || dif == -0.5 && (result & 1) != 0) result--;
            return result;
        }
    }
    throw new OverflowException(SR.Overflow_Int32);
}
```
