namespace BaiduBOSDemo
{
    using System.Threading;

    public class BOSDownloadRequestInfo
    {
        public string FilePath { get; set; }

        public string Bucket { get; set; }

        public string ObjectKey { get; set; }
        public long DownloadSize { get; set; } // Download Range
        public long DownloadedBytes { get; set; }

        public const string DownloadRequestInfoFileExtension = ".bosdownload.json";
        public const string DownloadingFileExtension = ".bosdownloading";
    }

    public class BOSDownloadRequest
    {
        public BOSDownloadRequestInfo RequestInfo { get; set; }

        public CancellationToken PauseCancellationToken { get; set; }

        public CancellationToken AbortCancellationToken { get; set; }
    }
}
