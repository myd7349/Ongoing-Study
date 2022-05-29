- https://github.com/protobuf-net/protobuf-net
  - https://github.com/AqlaSolutions/AqlaSerializer
- https://github.com/jskeet/protobuf-csharp-port
- https://github.com/googleapis/gapic-generator-csharp
- https://github.com/BlueMatthew/ProtobufInspector
- [IdleWakeups](https://github.com/google/IdleWakeups)

Articles:

- [Create Protobuf messages for .NET apps](https://learn.microsoft.com/en-us/aspnet/core/grpc/protobuf?view=aspnetcore-6.0)

- [深入 ProtoBuf - 编码](https://www.jianshu.com/p/73c9ed3a4877)

- Length-Delimited Protobuf Streams

  - [Protobuf In C# .NET – Part 3 – Using Length Prefixes](https://dotnetcoretutorials.com/2022/01/14/protobuf-in-c-net-part-3-using-length-prefixes/)

  - [Length-Delimited Protobuf Streams](https://seb-nyberg.medium.com/length-delimited-protobuf-streams-a39ebc4a4565)

  - [Is it possible to use google.protobuffer to serialize data without prefixing the length of each data field?](https://seb-nyberg.medium.com/length-delimited-protobuf-streams-a39ebc4a4565)

- [Google Protobuf Nullable Types](https://learn.microsoft.com/en-us/aspnet/core/grpc/protobuf?view=aspnetcore-6.0#nullable-types)

- [Can Nullable types be sent through Protocol Buffers?](https://stackoverflow.com/questions/43615583/can-nullable-types-be-sent-through-protocol-buffers)

- [Add option to generate C# nullable annotations](https://github.com/protocolbuffers/protobuf/issues/6632)

protobuf-net:

- [protobuf-net code generator](https://stackoverflow.com/questions/25452839/protobuf-net-code-generator)

- [Protobuf In C# .NET](https://dotnetcoretutorials.com/2022/01/13/protobuf-in-c-net-part-1-getting-started/)

  - [protogen](https://protogen.marcgravell.com/)

- [Protobuf-net object reference deserialization using Dictionary: A reference-tracked object changed reference during deserialization](https://stackoverflow.com/questions/14436606/protobuf-net-object-reference-deserialization-using-dictionary-a-reference-trac)

- [protobuf-net and serializing a linked list using interfaces](https://stackoverflow.com/questions/12623178/protobuf-net-and-serializing-a-linked-list-using-interfaces)

- [protobuf-net enum serialization](https://stackoverflow.com/questions/4135569/protobuf-net-enum-serialization)

- [protobuf-net do not serialize List<T>](https://stackoverflow.com/questions/13582208/protobuf-net-do-not-serialize-listt)

- [C#中protobuf-net的编码结构及使用方法](https://www.cnblogs.com/timefiles/p/protobuf-net.html)

- [Serializing WPF DrawingBrush with protobuf-net problems](https://stackoverflow.com/questions/10361220/serializing-wpf-drawingbrush-with-protobuf-net-problems)

  ```csharp
  RuntimeTypeModel.Default.Add(typeof(Color), false).Add("B", "G", "R", "A");
  ```

- [Protobuf-net pattern for optionally assignable nullable types (not collections)](https://stackoverflow.com/questions/62397017/protobuf-net-pattern-for-optionally-assignable-nullable-types-not-collections)

- [Problems serializing a list of nullable doubles using Protobuf-net](https://stackoverflow.com/questions/16756104/problems-serializing-a-list-of-nullable-doubles-using-protobuf-net)

- [protobuf.net Handling of Nullable<DateTimeOffset>](https://stackoverflow.com/questions/11426516/protobuf-net-handling-of-nullabledatetimeoffset)

- https://github.com/protobuf-net/protobuf-net/blob/main/src/Examples/Issues/Issue222.cs

- [Can I serialize arbitrary types with protobuf-net?](https://stackoverflow.com/questions/7046506/can-i-serialize-arbitrary-types-with-protobuf-net)

- [Generate optional ValueType field as Nullable<T>](https://github.com/protobuf-net/protobuf-net/issues/898)

  > Since Proto v3.15, optional is added back. So this keyword can be used in both proto2 and proto3 to represent a field is optional.

- [Does protobuf-net support nullable types?](https://stackoverflow.com/questions/4763875/does-protobuf-net-support-nullable-types)

- [How to use protobuf-net with immutable value types?](https://stackoverflow.com/questions/7120856/how-to-use-protobuf-net-with-immutable-value-types)

- [Sending explicit zeroes in protobuf3](https://stackoverflow.com/questions/61931285/sending-explicit-zeroes-in-protobuf3/61931373#61931373)
