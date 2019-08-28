namespace NDF
{
    using System;
    using System.Runtime.InteropServices;
    using System.Text;

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    internal struct NDFHeader
    {
        public static NDFHeader Default
        {
            get
            {
                var header = new NDFHeader();

                header.magic_ = Encoding.ASCII.GetBytes(NDF_MAGIC);
                header.IsLittleEndian = BitConverter.IsLittleEndian;
                header.ContainsMetaInfo = true;

                return header;
            }
        }

        public const int NDF_MAGIC_LENGTH = 6;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = NDF_MAGIC_LENGTH)]
        private byte[] magic_;

        private byte endian_;

        private byte containsMetaInfo_;

        public int DataLength;

        public string Magic
        {
            get
            {
                return Encoding.ASCII.GetString(magic_);
            }
        }

        public bool IsLittleEndian
        {
            get
            {
                if (endian_ == 'L')
                    return true;
                else if (endian_ == 'B')
                    return false;

                throw new Exception("Unknown endianess");
            }

            set
            {
                endian_ = (byte)(value ? 'L' : 'B');
            }
        }

        public bool ContainsMetaInfo
        {
            get
            {
                if (containsMetaInfo_ == 'Y')
                    return true;
                else if (containsMetaInfo_ == 'N')
                    return false;

                throw new Exception("Unknown meta information location");
            }

            set
            {
                containsMetaInfo_ = (byte)(value ? 'Y' : 'N');
            }
        }

        public bool IsValid
        {
            get
            {
                if (Magic != NDF_MAGIC)
                    return false;

                if (endian_ != 'L' && endian_ != 'B')
                    return false;

                if (containsMetaInfo_ != 'Y')
                {
                    if (containsMetaInfo_ == 'N')
                        throw new NotImplementedException("Meta info in seperated file is not supported yet");
                    else
                        return false;
                }

                if (DataLength < 0)
                    return false;

                return true;
            }
        }

        internal const string NDF_MAGIC = "SUxTTA";
        internal const int NDF_FILE_LENGTH_OFFSET = 6 + 1 + 1;
        internal const int NDF_FILE_HEADER_SIZE = NDF_FILE_LENGTH_OFFSET + 4;
    }
}
