namespace HDF5.Extension
{
    using System;

    public class HDF5Exception : Exception
    {
        public HDF5Exception(string message)
            : base(message)
        {
        }

        public HDF5Exception(string format, params object[] args)
            : this(string.Format(format, args))
        {
        }
    }
}
