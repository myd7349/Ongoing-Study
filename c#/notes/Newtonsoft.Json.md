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
