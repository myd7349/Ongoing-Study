[antchain-openapi-util-sdk/ErrRes.cs at e35bdb1afd1c34a40e16102c684a4bd05b2fd1a4 · alipay/antchain-openapi-util-sdk · GitHub](https://github.com/alipay/antchain-openapi-util-sdk/blob/e35bdb1afd1c34a40e16102c684a4bd05b2fd1a4/csharp/core/Models/ErrRes.cs#L4-L22)

> ```csharp
> using Newtonsoft.Json;
> 
> namespace AntChain.AlipayUtil.Models
> {
>     public class ErrRes
>     {
>         [JsonProperty(PropertyName = "response")]
>         public SubResponse Response { get; set; }
> 
>         [JsonProperty(PropertyName = "sign")]
>         public string Sign { get; set; }
> 
>         public class SubResponse
>         {
>             [JsonProperty(PropertyName = "result_code")]
>             public string ResultCode { get; set; }
>         }
>     }
> }
> ```


[Newtonsoft ignore attributes?](https://stackoverflow.com/questions/6309725/newtonsoft-ignore-attributes)

[Ignore Base Class Properties in Json.NET Serialization](https://stackoverflow.com/questions/31104335/ignore-base-class-properties-in-json-net-serialization)

[How to default a null JSON property to an empty array during serialization with a List<T> property in JSON.NET?](https://stackoverflow.com/questions/25148172/how-to-default-a-null-json-property-to-an-empty-array-during-serialization-with)

[Custom JsonConverter](https://www.newtonsoft.com/json/help/html/CustomJsonConverter.htm)

[custom serializer for just one property in Json.NET](https://stackoverflow.com/questions/18521970/custom-serializer-for-just-one-property-in-json-net)

[Newtonsoft.Json笔记 -JsonConverter](https://www.cnblogs.com/fanfan-90/p/13866912.html)

[How can I deserialize JSON to a simple Dictionary<string,string> in ASP.NET?](https://stackoverflow.com/questions/1207731/how-can-i-deserialize-json-to-a-simple-dictionarystring-string-in-asp-net)

[JavaScriptSerializer - JSON serialization of enum as string](https://stackoverflow.com/questions/2441290/javascriptserializer-json-serialization-of-enum-as-string)

[Serializing and Deserializing Enumerations with Json.NET](https://www.bytefish.de/blog/enums_json_net.html)

[How do I deserialize an array of enum using Json.Net?](https://stackoverflow.com/questions/23366364/how-do-i-deserialize-an-array-of-enum-using-json-net)

[Explanation for ObjectCreationHandling using Newtonsoft JSON?](https://stackoverflow.com/questions/27848547/explanation-for-objectcreationhandling-using-newtonsoft-json)

[ObjectCreationHandling setting](https://www.newtonsoft.com/json/help/html/DeserializeObjectCreationHandling.htm)

[Support ObjectCreationHandling in JsonSerializerOptions like Json.NET does](https://github.com/dotnet/runtime/issues/31518)

[Ignore Base Class Properties in Json.NET Serialization](https://stackoverflow.com/questions/31104335/ignore-base-class-properties-in-json-net-serialization)

[Json.net getter property not serialized](https://stackoverflow.com/questions/9727836/json-net-getter-property-not-serialized)

```csharp
class ClassWithoutDefaultConstructor
{
    public ClassWithoutDefaultConstructor(int arg1, int arg2)
    {
    }
}

var obj = JsonHelper.LoadJson<ClassWithoutDefaultConstructor>(jsonFilePath);

// Newtonsoft.Json.JsonSerializationException:“Unable to find a constructor to use for type ClassWithoutDefaultConstructor. A class should either have a default constructor, one constructor with arguments or a constructor marked with the JsonConstructor attribute. 
```

[JSON.net: how to deserialize without using the default constructor?](https://stackoverflow.com/questions/23017716/json-net-how-to-deserialize-without-using-the-default-constructor)

[JsonConstructorAttribute](https://www.newtonsoft.com/json/help/html/JsonConstructorAttribute.htm)

[How can I ignore unknown enum values during json deserialization?](https://stackoverflow.com/questions/22752075/how-can-i-ignore-unknown-enum-values-during-json-deserialization) (For example, you may have changed the name of an enumeration value in one of your code refactorings.)
