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

[minio-viewer](https://github.com/msgbyte/minio-viewer)

[How to use AWS SDK for .NET with MinIO Server](https://docs.min.io/docs/how-to-use-aws-sdk-for-net-with-minio-server.html)
