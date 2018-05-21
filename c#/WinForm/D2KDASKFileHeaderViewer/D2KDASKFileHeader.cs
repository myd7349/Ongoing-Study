namespace D2KDASKFileHeaderViewer
{
    using System.Runtime.InteropServices;
    using System.Text;

    public enum CardType : ushort
    {
        DAQ_2010 = 1,
        DAQ_2205,
        DAQ_2206,
        DAQ_2005,
        DAQ_2204,
        DAQ_2006,
        DAQ_2501,
        DAQ_2502,
        DAQ_2208,
        DAQ_2213,
        DAQ_2214,
        DAQ_2016,
        DAQ_2020,
        DAQ_2022  
    }

    public enum DataWidth : short
    {
        DataWidth8Bits = 0,
        DataWidth16Bits = 1,
        DataWidth32Bits = 2
    }

    public enum ChannelOrder : short
    {
        Normal = 0, // 0-1-2-3
        Reverse = 1, // 3-2-1-0
        Custom = 2 //
    }

    public enum ADRange : ushort
    {
        AD_B_10_V = 1,
        AD_B_5_V,
        AD_B_2_5_V,
        AD_B_1_25_V,
        AD_B_0_625_V,
        AD_B_0_3125_V,
        AD_B_0_5_V,
        AD_B_0_05_V,
        AD_B_0_005_V,
        AD_B_1_V,
        AD_B_0_1_V,
        AD_B_0_01_V,
        AD_B_0_001_V,
        AD_U_20_V,
        AD_U_10_V,
        AD_U_5_V,
        AD_U_2_5_V,
        AD_U_1_25_V,
        AD_U_1_V,
        AD_U_0_1_V,
        AD_U_0_01_V,
        AD_U_0_001_V,
        AD_B_2_V,
        AD_B_0_25_V,
        AD_B_0_2_V,
        AD_U_4_V,
        AD_U_2_V,
        AD_U_0_5_V,
        AD_U_0_4_V
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct ChannelRange
    {
        public byte Channel;
        public byte Range;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct D2KDASKFileHeader
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public byte[] IDBytes;
        public CardType CardType;
        public short Channels;
        public byte ChannelNo;
        public int NumberOfScans;
        public DataWidth DataWidth;
        public ChannelOrder ChannelOrder;
        public ADRange ADRange;
        public double ScanRate;
        public short NumberOfChannelRange;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] StartDateBytes;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] StartTimeBytes;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] StartMillisecondsBytes;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
        public byte[] Reserved;

        public string ID
        {
            get
            {
                return Encoding.ASCII.GetString(IDBytes);
            }
        }

        public string StartDate
        {
            get
            {
                return Encoding.ASCII.GetString(StartDateBytes);
            }
        }

        public string StartTime
        {
            get
            {
                return Encoding.ASCII.GetString(StartTimeBytes);
            }
        }

        public string StartMilliseconds
        {
            get
            {
                return Encoding.ASCII.GetString(StartMillisecondsBytes);
            }
        }
    }
}

// References:
// D2K-DASK Function Reference.pdf
// Appendix D Data File Format
// https://stackoverflow.com/questions/2793548/how-to-get-a-null-terminated-string-from-a-c-sharp-string
// https://stackoverflow.com/questions/8704161/c-sharp-array-within-a-struct
// https://stackoverflow.com/questions/11556852/marshal-not-0-terminated-string
// https://stackoverflow.com/questions/13915321/how-to-initialize-char-array-in-struct
// https://stackoverflow.com/questions/445749/c-sharp-3-byte-ints
// https://www.developerfusion.com/article/84519/mastering-structs-in-c/
// 
