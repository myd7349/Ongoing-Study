https://github.com/microsoft/perfview/blob/7bc1b55ebf6773f8afcdf46a96d2e9ccc763aeee/src/FastSerialization/FastSerialization.cs

> Sadly, System.Runtime.Serialization has a serious performance flaw. In the scheme created there, the basic contract between an object and the serializer is fundamentally heavy. For serialization the contract is for the object to implement System.Runtime.Serialization.ISerializable.GetObjectData and this should a series of AddValue() APIs on System.Runtime.Serialization.SerializationInfo which are given field names and values. The AddValue APIs box the values and place them in a table, It is then the serializers job to actually send out the bits given this table. The REQUIRED work of serializing an integers copying 4 bytes to some output buffer (a few instructions), however the protocol above requires 1000s.
