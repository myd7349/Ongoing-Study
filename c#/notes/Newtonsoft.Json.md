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

[JsonPropertyAttribute order](https://www.newtonsoft.com/json/help/html/JsonPropertyOrder.htm)

[Order of serialized fields using JSON.NET](https://stackoverflow.com/questions/3330989/order-of-serialized-fields-using-json-net)

```csharp
using System.Collections.Generic;

using Newtonsoft.Json;

namespace MyApp.Config
{
    public IPConfig
    {
        public string Address;

        public int Port;
    }

    [JsonObject(MemberSerialization.OptIn)]
    public class IPConfigGroup
    {
        // Consider moving the definition of SelectedGroup after the one of IPConfigurations.
        // Otherwise, there is a chance that SelectedGroup will be deserialized first when
        // deserializing. And at this time, IPConfigurations is still empty.
        [JsonProperty]
        public string SelectedGroup
        {
            get => selectedGroup_;

            set
            {
                if (SetProperty(ref selectedGroup_, value))
                {
                    // IPConfigurations might be empty here.
                    if (!IPConfigurations.ContainsKey(selectedGroup_))
                        IPConfigurations[selectedGroup_] = new IPConfig();

                    IPConfig = IPConfigurations[selectedGroup_];
                }
            }
        }

        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public Dictionary<string, IPConfig> IPConfigurations { get; set; }
            = new Dictionary<string, IPConfig>();

        public string Address
        {
            get => ipConfig_?.Address;

            set
            {
                if (ipConfig_ != null)
                    SetProperty(ref ipConfig_.Address, value);
            }
        }

        public int Port
        {
            get => ipConfig_?.Port ?? -1;

            set
            {
                if (ipConfig_ != null)
                    SetProperty(ref ipConfig_.Port, value);
            }
        }

        private IPConfig IPConfig
        {
            get => ipConfig_;

            set
            {
                if (ipConfig_ != value)
                {
                    ipConfig_ = value;

                    OnPropertyChanged(nameof(Address));
                    OnPropertyChanged(nameof(Port));
                }
            }
        }

        private string selectedGroup_;
        private IPConfig ipConfig_;
    }
}
```

[Json.net serialize specific private field](https://stackoverflow.com/questions/32008869/json-net-serialize-specific-private-field)

[How do I get json.net to serialize members of a class deriving from List<T>?](https://stackoverflow.com/questions/21265629/how-do-i-get-json-net-to-serialize-members-of-a-class-deriving-from-listt)

[Deep cloning objects](https://stackoverflow.com/questions/78536/deep-cloning-objects)

[.NET Serialization Performance Comparison](http://james.newtonking.com/archive/2010/01/01/net-serialization-performance-comparison)

[Overlay data from JSON string to existing object instance](https://stackoverflow.com/questions/5157079/overlay-data-from-json-string-to-existing-object-instance)

https://gist.github.com/cristi993/fe4ade633fcc304f4040

[Why don't people deep clone in C# by using a JObject one-liner?](https://stackoverflow.com/questions/66806219/why-dont-people-deep-clone-in-c-sharp-by-using-a-jobject-one-liner)

[Clear collections before adding items when populating existing objects](https://stackoverflow.com/questions/35482896/clear-collections-before-adding-items-when-populating-existing-objects)

```csharp
public class CollectionClearingContractResolver : DefaultContractResolver
{
    protected override JsonArrayContract CreateArrayContract(Type objectType)
    {
        var c = base.CreateArrayContract(objectType);
        c.OnDeserializingCallbacks.Add((obj, streamingContext) =>
        {
            var list = obj as IList;
            if (list != null && !list.IsReadOnly)
                list.Clear();
        });
        return c;
    }
}

...

public class Test {
    public List<int> List { get; private set; }
    public Test() {
        List = new List<int>();
    }
}  

...

var myObj = new Test();
myObj.List.AddRange(new[] {1,2,3});
var listReference = myObj.List;    

JsonConvert.PopulateObject("{ List: [4, 5, 6] }", myObj, 
    new JsonSerializerSettings {
        ContractResolver = new CollectionClearingContractResolver(),
    });

myObj.List.ShouldEqual(listReference); // didn't recreate list
myObj.List.Count.ShouldEqual(3);
myObj.List.SequenceEqual(new[] { 4, 5, 6}).ShouldBeTrue();
```

[How do I get Newtonsoft to serialize a bool as false, not False or "false"](https://stackoverflow.com/questions/54152416/how-do-i-get-newtonsoft-to-serialize-a-bool-as-false-not-false-or-false)

[Conditional serialization/deserialization of object properties with json.net](https://stackoverflow.com/questions/35502152/conditional-serialization-deserialization-of-object-properties-with-json-net)

[Conditional Property Serialization](https://www.newtonsoft.com/json/help/html/conditionalproperties.htm)
