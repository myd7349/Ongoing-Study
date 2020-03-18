namespace BaiduBOSDemo
{
    using System.Collections.Generic;
    using System.Threading;

    using BaiduBce.Services.Bos.Model;

    public class BOSMultipartUploadRequestInfo
    {
        public string FilePath { get; set; }

        public string Bucket { get; set; }

        public string ObjectKey { get; set; }

        public long PartSize { get; set; }

        public string UploadId { get; set; }

        public int LastPartNumber { get; set; }

        public List<PartETag> PartETags { get; set; }

        public const string UploadRequestInfoFileExtension = ".bosmultipartupload.json";
    }

    public class BOSMultipartUploadRequest
    {
        public BOSMultipartUploadRequestInfo RequestInfo { get; set; }

        public CancellationToken PauseCancellationToken { get; set; }

        public CancellationToken AbortCancellationToken { get; set; }
    }
}
