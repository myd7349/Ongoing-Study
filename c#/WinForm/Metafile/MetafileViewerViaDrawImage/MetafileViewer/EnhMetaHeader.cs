namespace MetafileViewer
{
    using System.ComponentModel;

    using Vanara.PInvoke;

    class EnhMetaHeader
    {
        public EnhMetaHeader(Gdi32.ENHMETAHEADER header)
        {
            header_ = header;
        }

        [Description("Whether any OpenGL records are present in the metafile.")]
        public bool IsOpenGL => header_.bOpenGL;

        [Description("The offset of pixel format used when recording the metafile.")]
        public uint OffsetOfPixelFormat => header_.offPixelFormat;

        [Description("The size of the last recorded pixel format in the metafile.")]
        public uint SizeOfPixelFormat => header_.cbPixelFormat;
  
        [Description("The resolution of the reference device, in millimeters.")]
        public SIZE ResolutionInMm => header_.szlMillimeters;

        [Description("The resolution of the reference device, in pixels.")]
        public SIZE ResolutionInPixels => header_.szlDevice;

        [Description("The number of entries in the enhanced metafile's palette.")]
        public uint PaletteEntriesCount => header_.nPalEntries;

        [Description("The offset from the beginning of the ENHMETAHEADER structure to the array that contains the description of the enhanced metafile's contents.")]
        public uint DescriptionOffset => header_.offDescription;

        [Description("The number of characters in the array that contains the description of the enhanced metafile's contents.")]
        public uint DescriptionLength => header_.nDescription;

        [Description("The number of handles in the enhanced-metafile handle table.")]
        public ushort HandlesCount => header_.nHandles;

        [Description("The number of records in the enhanced metafile.")]
        public uint RecordsCount => header_.nRecords;

        [Description("The size of the enhanced metafile, in bytes.")]
        public uint FileSize => header_.nBytes;

        [Description("The metafile version. The current version value is 0x10000.")]
        public uint Version => header_.nVersion;

        [Description("A signature. This member must specify the value assigned to the ENHMETA_SIGNATURE constant.")]
        public uint Signature => header_.dSignature;

        [Description("The dimensions, in .01 millimeter units, of a rectangle that surrounds the picture stored in the metafile.")]
        public RECT FrameRectangle => header_.rclFrame;

        [Description("The dimensions, in device units, of the smallest rectangle that can be drawn around the picture stored in the metafile.")]
        public RECT Bounds => header_.rclBounds;

        [Description("The structure size, in bytes.")]
        public uint HeaderSize => header_.nSize;

        [Description("The size of the reference device, in micrometers.")]
        public SIZE DeviceDimension => header_.szlMicrometers;

        [Description("The record type.")]
        public Gdi32.RecordType RecordType => header_.iType;

        private readonly Gdi32.ENHMETAHEADER header_;
    }
}
