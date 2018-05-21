namespace D2KDASKFileHeaderViewer
{
    using System.ComponentModel;

    [TypeConverter(typeof(ExpandableObjectConverter))]
    public sealed class D2KDASKFileHeaderWrapper
    {
        public D2KDASKFileHeaderWrapper(D2KDASKFileHeader header)
        {
            this.header = header;
        }

        [DisplayName("File ID")]
        public string ID { get { return header.ID; } }

        [DisplayName("Card Type")]
        public CardType CardType { get { return header.CardType; } }

        [DisplayName("Number of Channels")]
        [Description("Number of scanned channels")]
        public short Channels { get { return header.Channels; } }

        [Description(@"Channel number where data is read from.
Only available as the Number of Channels is 1.")]
        public byte ChannelNo { get { return header.ChannelNo; } }

        [DisplayName("Number of scanns")]
        [Description("Number of scan for each channel.")]
        public int NumberOfScans { get { return header.NumberOfScans; } }

        [DisplayName("Data Width")]
        [Description("Data width (0: 8 bits, 1: 16 bits, 2: 32 bits).")]
        public DataWidth DataWidth { get { return header.DataWidth; } }

        [DisplayName("Channel Order")]
        [Description(@"Channel scanned sequence 
0: normal (0-1-2-3)
1: reverse (3-2-1-0)
2: custom* (0, 1, 3), (0, 1, 0, 2)")]
        public ChannelOrder ChannelOrder { get { return header.ChannelOrder; } }

        [DisplayName("AD Range")]
        [Description("AI range code. Refer to Appendix B.")]
        public ADRange ADRange { get { return header.ADRange; } }

        [DisplayName("Scan Rate")]
        [Description("Scanning rate of each channel (total sampling rate / num_of_channel).")]
        public double ScanRate { get { return header.ScanRate; } }

        [DisplayName("Number of Channel Range")]
        [Description("Number of ChannelRange* structure after the header.")]
        public short NumberOfChannelRange { get { return header.NumberOfChannelRange; } }

        [DisplayName("Start Date")]
        [Description("Starting date of data acquisition(12/31/99, for example).")]
        public string StartDate { get { return header.StartDate; } }

        [DisplayName("Start Time")]
        [Description("Starting time of data acquisition(18:30:25, for example).")]
        public string StartTime { get { return header.StartTime; } }

        [DisplayName("Start Milliseconds")]
        [Description("Starting millisecond of data acquisition.")]
        public string StartMilliseconds { get { return header.StartMilliseconds; } }

        private D2KDASKFileHeader header;
    }
}

// References:
// https://stackoverflow.com/questions/7422685/edit-the-display-name-of-enumeration-members-in-a-propertygrid
