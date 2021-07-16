[Download an object with an progress bar](https://github.com/minio/minio-dotnet/blob/ef75b2fe96840ad48ddbe62ae19d3d31e9f41904/Minio/ApiEndpoints/ObjectOperations.cs#L78)

```csharp
long offset = 0;
int partBytes = 51200;
var bytes = new byte[partBytes];

while (offset < objectTotalBytes)
{
    if (offset + partBytes > objectTotalBytes)
        partBytes = objectTotalBytes - offset;

    await GetObjectAsync(bucketName, objectName, offset, partBytes, 
        (stream) =>
        {
            var bytesRead = stream.Read(bytes, 0, partBytes);
            fileStream.Write(bytes, 0, bytesRead);
            
            offset += bytesRead;
        });
}
```

It will be very SLOW!!!

```csharp
long offset = 0;
int partBytes = 51200;
var bytes = new byte[partBytes];

while (offset < objectTotalBytes)
{
    if (offset + partBytes > objectTotalBytes)
        partBytes = objectTotalBytes - offset;

    await GetObjectAsync(bucketName, objectName, offset, partBytes, 
        (stream) =>
        {
            stream.CopyTo(fileStream);
        });
    
    offset += partBytes;
}
```

