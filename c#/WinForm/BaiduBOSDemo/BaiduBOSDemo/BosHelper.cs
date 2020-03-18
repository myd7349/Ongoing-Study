namespace BaiduBOSDemo
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Threading;
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
            /*
            BaiduBce.BceServiceException
            HResult=0x80131500
            Message=Your request is denied because there is an overdue bill of your account. (Status Code: 403; Error Code: AccountOverdue; Request ID: e1c9e259-1ede-4bff-aba3-d3a75186c095)
            Source=BceSdkDotNet
            */
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

        public static Task<bool> UploadFileAsync(this BosClient bosClient,
            string bucket, string key, string filePath,
            CancellationToken pausecancellationToken,
            CancellationToken abortCancellationToken,
            IProgress<int> onProgressPercentChanged)
        {
            return Task.Run(() => bosClient.UploadFile(bucket, key, filePath,
                pausecancellationToken, abortCancellationToken,
                onProgressPercentChanged));
        }

        public static bool UploadFile(this BosClient bosClient, string bucket, string key, string filePath,
            CancellationToken pauseCancellationToken, CancellationToken abortCancellationToken,
            IProgress<int> onProgressPercentChanged)
        {
            if (!File.Exists(filePath))
                return false;

            var fileInfo = new FileInfo(filePath);

            long partSize = 1024 * 1024 * 5;
            
            int parts = (int)(fileInfo.Length / partSize);
            if (fileInfo.Length % partSize != 0)
                parts += 1;

            var partETags = new List<PartETag>();

            var initiateMultipartUploadRequest =
                new InitiateMultipartUploadRequest()
                {
                    BucketName = bucket,
                    Key = key
                };
            var initiateMultipartUploadResponse = bosClient.InitiateMultipartUpload(initiateMultipartUploadRequest);

            for (int i = 0; i < parts; ++i)
            {
                if (pauseCancellationToken.IsCancellationRequested)
                    return false;

                if (abortCancellationToken.IsCancellationRequested)
                {
                    var abortMultipartUploadRequest = new AbortMultipartUploadRequest()
                    {
                        BucketName = bucket,
                        Key = key,
                        UploadId = initiateMultipartUploadResponse.UploadId,
                    };
                    bosClient.AbortMultipartUpload(abortMultipartUploadRequest);

                    return false;
                }

                using (var stream = fileInfo.OpenRead()) // TODO:
                {
                    var skipBytes = partSize * i;
                    stream.Seek(skipBytes, SeekOrigin.Begin);

                    onProgressPercentChanged?.Report((int)(((double)skipBytes / fileInfo.Length) * 100));

                    var actualPartSize = Math.Min(partSize, fileInfo.Length - skipBytes);

                    var uploadPartRequest = new UploadPartRequest();
                    uploadPartRequest.BucketName = bucket;
                    uploadPartRequest.Key = key;
                    uploadPartRequest.UploadId = initiateMultipartUploadResponse.UploadId;
                    uploadPartRequest.InputStream = stream;
                    uploadPartRequest.PartSize = actualPartSize;
                    uploadPartRequest.PartNumber = i + 1;

                    var uploadPartResponse = bosClient.UploadPart(uploadPartRequest);

                    partETags.Add(
                        new PartETag()
                        {
                            ETag = uploadPartResponse.ETag,
                            PartNumber = uploadPartResponse.PartNumber
                        });
                }
            }

            var completeMultipartUploadRequest =
                new CompleteMultipartUploadRequest()
                {
                    BucketName = bucket,
                    Key = key,
                    UploadId = initiateMultipartUploadResponse.UploadId,
                    PartETags = partETags
                };

            var completeMultipartUploadResponse = bosClient.CompleteMultipartUpload(completeMultipartUploadRequest);

            onProgressPercentChanged?.Report(100);

            return completeMultipartUploadResponse != null;
        }
    }
}

// References:
// https://stackoverflow.com/questions/9459225/asynchronous-file-download-with-progress-bar
// http://simplygenius.net/Article/AncillaryAsyncProgress
