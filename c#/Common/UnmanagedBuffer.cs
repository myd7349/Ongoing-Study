namespace Common
{
    using System;
    using System.Runtime.InteropServices;

    using Common;

    public sealed class UnmanagedBuffer : IDisposable
    {
        public static implicit operator IntPtr(UnmanagedBuffer buffer)
        {
            return buffer.handle_;
        }

        public UnmanagedBuffer(int bytes)
        {
            if (bytes <= 0)
                throw new ArgumentOutOfRangeException("bytes");

            bytes_ = bytes;
            handle_ = Marshal.AllocHGlobal(bytes_);
        }

        // NOTE: Leave out the finalizer altogether if this class doesn't
        // own unmanaged resources, but leave the other methods
        // exactly as they are.
        ~UnmanagedBuffer()
        {
            // Finalizer calls Dispose(false)
            Dispose(false);
        }

        // TODO: Convert.ChangeType
        public void Write<T>(T value)
        {
            var type = typeof(T);
            if (Marshal.SizeOf(type) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            switch (Type.GetTypeCode(type))
            {
                case TypeCode.SByte:
                    MarshalHelper.WriteSByte(handle_, Convert.ToSByte(value));
                    break;
                case TypeCode.Byte:
                    Marshal.WriteByte(handle_, Convert.ToByte(value));
                    break;
                case TypeCode.Int16:
                    Marshal.WriteInt16(handle_, Convert.ToInt16(value));
                    break;
                case TypeCode.UInt16:
                    MarshalHelper.WriteUInt16(handle_, Convert.ToUInt16(value));
                    break;
                case TypeCode.Int32:
                    Marshal.WriteInt32(handle_, Convert.ToInt32(value));
                    break;
                case TypeCode.UInt32:
                    MarshalHelper.WriteUInt32(handle_, Convert.ToUInt32(value));
                    break;
                case TypeCode.Int64:
                    Marshal.WriteInt64(handle_, Convert.ToInt64(value));
                    break;
                case TypeCode.UInt64:
                    MarshalHelper.WriteUInt64(handle_, Convert.ToUInt64(value));
                    break;
                case TypeCode.Single:
                    MarshalHelper.WriteSingle(handle_, Convert.ToSingle(value));
                    break;
                case TypeCode.Double:
                    MarshalHelper.WriteDouble(handle_, Convert.ToDouble(value));
                    break;
                default:
                    throw new ArgumentException("Only primitive data types are supported.");
            }
        }

        // TODO: Convert.ChangeType
        public void WriteEnum<T>(T value)
        {
            var type = typeof(T);
            if (!type.IsEnum)
                throw new ArgumentException("Not a enum type.");

            var underlyingType = Enum.GetUnderlyingType(typeof(T));
            switch (Type.GetTypeCode(underlyingType))
            {
                case TypeCode.SByte:
                    Write(Convert.ToSByte(value));
                    break;
                case TypeCode.Byte:
                    Write(Convert.ToByte(value));
                    break;
                case TypeCode.Int16:
                    Write(Convert.ToInt16(value));
                    break;
                case TypeCode.UInt16:
                    Write(Convert.ToUInt16(value));
                    break;
                case TypeCode.Int32:
                    Write(Convert.ToInt32(value));
                    break;
                case TypeCode.UInt32:
                    Write(Convert.ToUInt32(value));
                    break;
                case TypeCode.Int64:
                    Write(Convert.ToInt64(value));
                    break;
                case TypeCode.UInt64:
                    Write(Convert.ToUInt64(value));
                    break;
                default:
                    throw new Exception(string.Format("Unexpected enum underlying type {0}.", underlyingType));
            }
        }

        public object Read(Type type)
        {
            if (Marshal.SizeOf(type) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            switch (Type.GetTypeCode(type))
            {
                case TypeCode.SByte:
                    return MarshalHelper.ReadSByte(handle_);
                case TypeCode.Byte:
                    return Marshal.ReadByte(handle_);
                case TypeCode.Int16:
                    return Marshal.ReadInt16(handle_);
                case TypeCode.UInt16:
                    return MarshalHelper.ReadUInt16(handle_);
                case TypeCode.Int32:
                    return Marshal.ReadInt32(handle_);
                case TypeCode.UInt32:
                    return MarshalHelper.ReadUInt32(handle_);
                case TypeCode.Int64:
                    return Marshal.ReadInt64(handle_);
                case TypeCode.UInt64:
                    return MarshalHelper.ReadUInt64(handle_);
                case TypeCode.Single:
                    return MarshalHelper.ReadSingle(handle_);
                case TypeCode.Double:
                    return MarshalHelper.ReadDouble(handle_);
                default:
                    throw new ArgumentException("Only primitive data types are supported.");
            }
        }

        public T Read<T>()
        {
            return (T)Read(typeof(T));
        }

        public T ReadEnum<T>()
        {
            var type = typeof(T);
            if (!type.IsEnum)
                throw new ArgumentException("Not a enum type.");

            var underlyingType = Enum.GetUnderlyingType(typeof(T));
            return (T)Read(underlyingType);
        }

        public sbyte ReadSByte()
        {
            if (sizeof(sbyte) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return MarshalHelper.ReadSByte(handle_);
        }

        public byte ReadByte()
        {
            if (sizeof(byte) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return Marshal.ReadByte(handle_);
        }

        public short ReadInt16()
        {
            if (sizeof(short) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return Marshal.ReadInt16(handle_);
        }

        public ushort ReadUInt16()
        {
            if (sizeof(ushort) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return MarshalHelper.ReadUInt16(handle_);
        }

        public int ReadInt32()
        {
            if (sizeof(int) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return Marshal.ReadInt32(handle_);
        }

        public uint ReadUInt32()
        {
            if (sizeof(uint) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return MarshalHelper.ReadUInt32(handle_);
        }

        public long ReadInt64()
        {
            if (sizeof(long) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return Marshal.ReadInt64(handle_);
        }

        public ulong ReadUInt64()
        {
            if (sizeof(ulong) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return MarshalHelper.ReadUInt64(handle_);
        }

        public float ReadSingle()
        {
            if (sizeof(float) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return MarshalHelper.ReadSingle(handle_);
        }

        public double ReadDouble()
        {
            if (sizeof(double) != bytes_)
                throw new ArgumentException("Unmatched buffer size.");

            return MarshalHelper.ReadDouble(handle_);
        }

        public void CopyFrom(byte[] source, int start, int count)
        {
            Marshal.Copy(source, start, handle_, count);
        }

        public void CopyFrom(int[] source, int start, int count)
        {
            Marshal.Copy(source, start, handle_, count);
        }

        public void CopyFrom(double[] source, int start, int count)
        {
            Marshal.Copy(source, start, handle_, count);
        }

        public void CopyTo(byte[] dest, int start, int count)
        {
            Marshal.Copy(handle_, dest, start, count);
        }

        public void CopyTo(int[] dest, int start, int count)
        {
            Marshal.Copy(handle_, dest, start, count);
        }

        public void CopyTo(double[] dest, int start, int count)
        {
            Marshal.Copy(handle_, dest, start, count);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (disposed_)
                return;

            if (disposing)
            {
                // Free managed resources
                // 1.
            }

            // Free native resources if there are any.
            // 2.
            Marshal.FreeHGlobal(handle_);

            disposed_ = true;
        }

        private int bytes_;
        private IntPtr handle_;
        private bool disposed_ = false;
    }
}

// References:
// [How to get IntPtr from byte[] in C#](https://stackoverflow.com/questions/537573/how-to-get-intptr-from-byte-in-c-sharp)
// [CA1063: Implement IDisposable correctly](https://docs.microsoft.com/en-us/dotnet/fundamentals/code-analysis/quality-rules/ca1063)
// https://referencesource.microsoft.com/#system/compmod/microsoft/win32/safehandles/SafeLibraryHandle.cs
// [How to instance a C# class in UNmanaged memory? (Possible?)](https://stackoverflow.com/questions/10800063/how-to-instance-a-c-sharp-class-in-unmanaged-memory-possible)
// [How to find out if a numeric type is signed or unsigned in C#](https://stackoverflow.com/questions/53300136/how-to-find-out-if-a-numeric-type-is-signed-or-unsigned-in-c-sharp)
// [How do I cast a generic enum to int?](https://stackoverflow.com/questions/16960555/how-do-i-cast-a-generic-enum-to-int)
// [Cast Int to Generic Enum in C#](https://stackoverflow.com/questions/10387095/cast-int-to-generic-enum-in-c-sharp)
// [How do I cast a generic enum to int?](https://stackoverflow.com/questions/16960555/how-do-i-cast-a-generic-enum-to-int)
// [Cast Int to Generic Enum in C#](https://stackoverflow.com/questions/10387095/cast-int-to-generic-enum-in-c-sharp)
// [c# P/Invoke : Pass Enum value with IntPtr to Function; AccessViolationException](https://stackoverflow.com/questions/47723953/c-sharp-p-invoke-pass-enum-value-with-intptr-to-function-accessviolationexcep)
// [How to convert from System.Enum to base integer?](https://stackoverflow.com/questions/908543/how-to-convert-from-system-enum-to-base-integer)
// SafeHeapBlock: https://github.com/dahall/Vanara/blob/56cda5a8f4d6648563651996d99f471f9e49e56f/PInvoke/Kernel32/HeapApi.cs#L1411
// https://github.com/dahall/Vanara/blob/8ca58cc2c8d5ca87c19a434f06b6b2f6810aa313/Core/InteropServices/SafeHGlobalHandle.cs#L117
// public static SafeHGlobalHandle CreateFromStructure<T>(in T value = default) => new SafeHGlobalHandle(InteropExtensions.MarshalToPtr(value, mm.AllocMem, out int s), s);
// [C# performance - Using unsafe pointers instead of IntPtr and Marshal](https://stackoverflow.com/questions/17549123/c-sharp-performance-using-unsafe-pointers-instead-of-intptr-and-marshal)
// > I would suppose that the slowness of the third case was due to AllocHGlobal which has a higher per-call overhead.
