namespace BaiduBOSDemo
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Linq;
    using System.Threading;
    using BaiduBce.Services.Bos;
    using BaiduBce.Services.Bos.Model;

    public static class BOSHelper
    {
        public static IEnumerable<string> GetBuckets(this BosClient bosClient)
        {
            return bosClient.ListBuckets().Buckets.Select(bucketSummary => bucketSummary.Name);
        }

        public static IEnumerable<BosObjectSummary> GetObjects(this BosClient bosClient, string bucket)
        {
            var response = bosClient.ListObjects(bucket);
            return response.Contents;
        }

        public static bool UploadFile(this BosClient bosClient, string bucket, string key, string filePath, CancellationToken cancellationToken)
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

            using (var stream = fileInfo.OpenRead())
            {
                for (int i = 0; i < parts; ++i)
                {
                    var skipBytes = partSize * i;
                    stream.Seek(skipBytes, SeekOrigin.Begin);

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

            return completeMultipartUploadResponse != null;
        }
    }
}

// References:
// https://stackoverflow.com/questions/9459225/asynchronous-file-download-with-progress-bar
// http://simplygenius.net/Article/AncillaryAsyncProgress
