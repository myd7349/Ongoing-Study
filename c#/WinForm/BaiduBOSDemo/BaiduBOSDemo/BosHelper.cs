namespace BaiduBOSDemo
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.IO;
    using System.Linq;
    using System.Threading.Tasks;

    using BaiduBce;
    using BaiduBce.Auth;
    using BaiduBce.Services.Bos;
    using BaiduBce.Services.Bos.Model;

    public static class BOSHelper
    {
        public static BosClient CreateBosClient(Settings settings)
        {
            BceClientConfiguration clientConfig = new BceClientConfiguration();
            clientConfig.Credentials = new DefaultBceCredentials(settings.AccessKey, settings.SecretAccessKey);
            clientConfig.Endpoint = settings.EndPoint;

            return new BosClient(clientConfig);
        }

        public static Task<IEnumerable<string>> GetBucketsAsync(this BosClient bosClient)
        {
            return Task.Run(() => bosClient.ListBuckets().Buckets.Select(bucketSummary => bucketSummary.Name));
        }

        public static Task<List<BosObjectSummary>> GetObjectsAsync(this BosClient bosClient, string bucket)
        {
            return Task.Run(() => bosClient.ListObjects(bucket).Contents);
        }

        public static Task<List<BosObjectSummary>> GetObjectsAsync(this BosClient bosClient, string bucket, string prefix, string delimiter = "")
        {
            return Task.Run(
                () =>
                {
                    var listObjectsRequest = new ListObjectsRequest { BucketName = bucket };
                    listObjectsRequest.Prefix = prefix;
                    listObjectsRequest.Delimiter = delimiter;

                    return bosClient.ListObjects(listObjectsRequest).Contents;
                });
        }

        public static Task DeleteObjectsAsync(this BosClient bosClient, string bucketName, params string[] objects)
        {
            return Task.Run(() => { foreach (var objectKey in objects) bosClient.DeleteObject(bucketName, objectKey); });
        }

        public static Task<bool> UploadFileAsync(this BosClient bosClient, BOSMultipartUploadRequest bosUploadRequest, IProgress<int> onProgressPercentChanged)
        {
            return Task.Run(() => bosClient.UploadFile(bosUploadRequest, onProgressPercentChanged));
        }

        public static bool UploadFile(this BosClient bosClient, BOSMultipartUploadRequest bosUploadRequest, IProgress<int> onProgressPercentChanged)
        {
            Debug.Assert(bosUploadRequest.RequestInfo.PartSize > 0);
            var filePath = bosUploadRequest.RequestInfo.FilePath;
            if (!File.Exists(filePath))
                return false;

            var fileInfo = new FileInfo(filePath);

            long partSize = bosUploadRequest.RequestInfo.PartSize;
            
            int parts = (int)(fileInfo.Length / partSize);
            if (fileInfo.Length % partSize != 0)
                parts += 1;

            if (bosUploadRequest.RequestInfo.PartETags == null)
                bosUploadRequest.RequestInfo.PartETags = new List<PartETag>();

            if (string.IsNullOrEmpty(bosUploadRequest.RequestInfo.UploadId))
            {
                var initiateMultipartUploadRequest = new InitiateMultipartUploadRequest()
                {
                    BucketName = bosUploadRequest.RequestInfo.Bucket,
                    Key = bosUploadRequest.RequestInfo.ObjectKey
                };
                var initiateMultipartUploadResponse = bosClient.InitiateMultipartUpload(initiateMultipartUploadRequest);

                bosUploadRequest.RequestInfo.UploadId = initiateMultipartUploadResponse.UploadId;
            }
            
            var uploadId = bosUploadRequest.RequestInfo.UploadId;

            for (int i = bosUploadRequest.RequestInfo.LastPartNumber; i < parts; ++i)
            {
                if (bosUploadRequest.PauseCancellationToken.IsCancellationRequested)
                    return false;

                if (bosUploadRequest.AbortCancellationToken.IsCancellationRequested)
                {
                    var abortMultipartUploadRequest = new AbortMultipartUploadRequest()
                    {
                        BucketName = bosUploadRequest.RequestInfo.Bucket,
                        Key = bosUploadRequest.RequestInfo.ObjectKey,
                        UploadId = uploadId,
                    };
                    bosClient.AbortMultipartUpload(abortMultipartUploadRequest);

                    return false;
                }

                using (var stream = fileInfo.OpenRead())
                {
                    var skipBytes = partSize * i;
                    stream.Seek(skipBytes, SeekOrigin.Begin);

                    onProgressPercentChanged?.Report((int)(((double)skipBytes / fileInfo.Length) * 100));

                    var actualPartSize = Math.Min(partSize, fileInfo.Length - skipBytes);

                    var uploadPartRequest = new UploadPartRequest();
                    uploadPartRequest.BucketName = bosUploadRequest.RequestInfo.Bucket;
                    uploadPartRequest.Key = bosUploadRequest.RequestInfo.ObjectKey;
                    uploadPartRequest.UploadId = uploadId;
                    uploadPartRequest.InputStream = stream;
                    uploadPartRequest.PartSize = actualPartSize;
                    uploadPartRequest.PartNumber = i + 1;

                    var uploadPartResponse = bosClient.UploadPart(uploadPartRequest);

                    bosUploadRequest.RequestInfo.PartETags.Add(
                        new PartETag()
                        {
                            ETag = uploadPartResponse.ETag,
                            PartNumber = uploadPartResponse.PartNumber
                        });

                    bosUploadRequest.RequestInfo.LastPartNumber = uploadPartResponse.PartNumber;
                }
            }

            var completeMultipartUploadRequest =
                new CompleteMultipartUploadRequest()
                {
                    BucketName = bosUploadRequest.RequestInfo.Bucket,
                    Key = bosUploadRequest.RequestInfo.ObjectKey,
                    UploadId = uploadId,
                    PartETags = bosUploadRequest.RequestInfo.PartETags
                };

            var completeMultipartUploadResponse = bosClient.CompleteMultipartUpload(completeMultipartUploadRequest);

            onProgressPercentChanged?.Report(100);

            return completeMultipartUploadResponse != null;
        }

        public static Task<bool> DownloadFileAsync(this BosClient bosClient, BOSDownloadRequest bosDownloadRequest, IProgress<int> onProgressPercentChanged)
        {
            return Task.Run(() => bosClient.DownloadFile(bosDownloadRequest, onProgressPercentChanged));
        }

        public static bool DownloadFile(this BosClient bosClient, BOSDownloadRequest bosDownloadRequest, IProgress<int> onProgressPercentChanged)
        {
            Debug.Assert(bosDownloadRequest.RequestInfo.DownloadSize > 0);
            Debug.Assert(bosDownloadRequest.RequestInfo.DownloadedBytes % bosDownloadRequest.RequestInfo.DownloadSize == 0);

            var filePath = bosDownloadRequest.RequestInfo.FilePath;

            var getObjectRequest = new GetObjectRequest
            {
                BucketName = bosDownloadRequest.RequestInfo.Bucket,
                Key = bosDownloadRequest.RequestInfo.ObjectKey,
            };

            var objectMetadata = bosClient.GetObjectMetadata(getObjectRequest);
            var fileLength = objectMetadata.ContentLength;
            Debug.Assert(bosDownloadRequest.RequestInfo.DownloadedBytes < fileLength);

            using (var stream = File.OpenWrite(filePath))
            {
                if (bosDownloadRequest.RequestInfo.DownloadedBytes == 0)
                {
                    // This doesn't work:
                    //stream.Seek(fileLength, SeekOrigin.Begin);
                    stream.SetLength(fileLength);
                }

                stream.Seek(bosDownloadRequest.RequestInfo.DownloadedBytes, SeekOrigin.Begin);

                int parts = (int)(fileLength / bosDownloadRequest.RequestInfo.DownloadSize);
                if (fileLength % bosDownloadRequest.RequestInfo.DownloadSize != 0)
                    parts += 1;


                for (int i = (int)(bosDownloadRequest.RequestInfo.DownloadedBytes / bosDownloadRequest.RequestInfo.DownloadSize);
                    i < parts;
                    ++i)
                {
                    if (bosDownloadRequest.PauseCancellationToken.IsCancellationRequested)
                        return false;

                    if (bosDownloadRequest.AbortCancellationToken.IsCancellationRequested)
                    {
                        stream.Close();
                        return false;
                    }
                    
                    var startBytes = bosDownloadRequest.RequestInfo.DownloadSize * i;
                    var endBytes = startBytes + bosDownloadRequest.RequestInfo.DownloadSize - 1;
                    if (endBytes > fileLength)
                        endBytes = fileLength;

                    onProgressPercentChanged?.Report((int)(((double)startBytes / fileLength) * 100));

                    getObjectRequest.SetRange(startBytes, endBytes);
                    var bosObject = bosClient.GetObject(getObjectRequest);
                    bosObject.ObjectContent.CopyTo(stream);

                    bosDownloadRequest.RequestInfo.DownloadedBytes += endBytes + 1 - startBytes;
                }

                onProgressPercentChanged?.Report(100);
            }

            return true;
        }
    }
}

// References:
// https://stackoverflow.com/questions/9459225/asynchronous-file-download-with-progress-bar
// http://simplygenius.net/Article/AncillaryAsyncProgress
// https://stackoverflow.com/questions/8416413/create-new-file-with-specific-size
