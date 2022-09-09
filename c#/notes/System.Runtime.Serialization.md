https://github.com/microsoft/perfview/blob/7bc1b55ebf6773f8afcdf46a96d2e9ccc763aeee/src/FastSerialization/FastSerialization.cs

> Sadly, System.Runtime.Serialization has a serious performance flaw. In the scheme created there, the basic contract between an object and the serializer is fundamentally heavy. For serialization the contract is for the object to implement System.Runtime.Serialization.ISerializable.GetObjectData and this should a series of AddValue() APIs on System.Runtime.Serialization.SerializationInfo which are given field names and values. The AddValue APIs box the values and place them in a table, It is then the serializers job to actually send out the bits given this table. The REQUIRED work of serializing an integers copying 4 bytes to some output buffer (a few instructions), however the protocol above requires 1000s.

https://github.com/reactiveui/Camelotia/blob/main/src/Camelotia.Services/Configuration/CloudConfiguration.cs

[Fastest Way to do Shallow Copy in C#](https://stackoverflow.com/questions/966451/fastest-way-to-do-shallow-copy-in-c-sharp)

[C# Object Clone Wars](https://www.csharp411.com/c-object-clone-wars/)

[What is the method MemberwiseClone() doing?](https://stackoverflow.com/questions/2289420/what-is-the-method-memberwiseclone-doing)

https://github.com/force-net/DeepCloner/blob/develop/DeepCloner/Helpers/ShallowObjectCloner.cs

[Deep cloning objects](https://stackoverflow.com/questions/78536/deep-cloning-objects)

[5 Ways to Clone An Object in C#](https://levelup.gitconnected.com/5-ways-to-clone-an-object-in-c-d1374ec28efa)

[Recursive deep cloning](https://github.com/AutoMapper/AutoMapper/issues/340)

> Because AutoMapper is a lousy solution for cloning. I've always had more success with the BinaryFormatter approach.

[Why is AutoMapper Creating Shallow Copies?](https://stackoverflow.com/questions/31623279/why-is-automapper-creating-shallow-copies)

[Create Deep Copies Of Object In C# Using AutoMapper](https://jshowers.com/create-deep-copies-of-object-in-c-using-automapper/)

[Deep Copy Using AutoMapper](https://www.codeproject.com/Articles/1107342/Deep-Copy-Using-AutoMapper)

```csharp
public static T DeepCopy<T>(T obj)
{
    if (obj == null)
    {
        return default(T);
    }
    using (var memoryStream = new MemoryStream())
    {
        var formatter = new BinaryFormatter();
        formatter.Serialize(memoryStream, obj);
        memoryStream.Seek(0, SeekOrigin.Begin);
        return (T)formatter.Deserialize(memoryStream);
    }
}
```

[How do you do a deep copy of an object in .NET?](https://stackoverflow.com/questions/129389/how-do-you-do-a-deep-copy-of-an-object-in-net)

[Fast Deep Copy by Expression Trees (C#)](https://www.codeproject.com/Articles/1111658/Fast-Deep-Copy-by-Expression-Trees-C-Sharp)

> The best working, tested and shortest by amount of code is Serialization through BinaryFormatter (code 1, code 2). Though it is the slowest possibility and requires the Serializable attribute, it clones very well everything what our solution does and furthermore does some copy of Delegates and Events. It passed all tests too.

EnumMember

- [JavaScriptSerializer - JSON serialization of enum as string](https://stackoverflow.com/questions/2441290/javascriptserializer-json-serialization-of-enum-as-string)
