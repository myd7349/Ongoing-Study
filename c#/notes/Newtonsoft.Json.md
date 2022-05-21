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
