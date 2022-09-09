namespace Common.Collections.Generic
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Linq;
    using System.Text;

    public class CircularBuffer<T> : ICollection<T>
        where T : struct
    {
        public CircularBuffer(int capacity, bool overwrite = false)
        {
            if (capacity <= 0)
                throw new ArgumentException("capacity");

            buffer_ = new T[capacity];
            Overwrite = overwrite;
        }

        #region ICollection<T>
        public int Count { get; private set; } = 0;

        public bool IsReadOnly
        {
            get
            {
                return false;
            }
        }

        public void Add(T item)
        {
            if (Count == Capacity)
                throw new InvalidOperationException("full");

            buffer_[fillPtr_] = item;
            Count += 1;
            fillPtr_ = (fillPtr_ + 1) % Capacity;
        }

        public void Clear()
        {
            fillPtr_ = usePtr_ = 0;
            Count = 0;
        }

        public bool Contains(T item)
        {
            if (IsEmpty)
                return false;

            if (Count == Capacity)
                return buffer_.Contains(item);

            if (usePtr_ + Count <= fillPtr_)
            {
                for (int i = usePtr_; i < fillPtr_; ++i)
                {
                    if (buffer_[i].Equals(item))
                        return true;
                }

                return false;
            }
            else
            {
                for (int i = usePtr_; i < buffer_.Length; ++i)
                {
                    if (buffer_[i].Equals(item))
                        return true;
                }

                for (int i = 0; i < fillPtr_; ++i)
                {
                    if (buffer_[i].Equals(item))
                        return true;
                }

                return false;
            }
        }

        // Queue.cs
        public void CopyTo(T[] array, int arrayIndex)
        {
            if (array == null)
                throw new ArgumentNullException(nameof(array));

            if (arrayIndex < 0 || arrayIndex > array.Length)
                throw new ArgumentOutOfRangeException(nameof(arrayIndex), arrayIndex, "Argument out of range");

            if (array.Length - arrayIndex < Count)
                throw new ArgumentException("No enough space"); // TODO: Should old elements be overwritten?

            if (IsEmpty)
                return;

            if (usePtr_ < fillPtr_)
            {
                Array.Copy(buffer_, usePtr_, array, arrayIndex, Count);
            }
            else
            {
                Array.Copy(buffer_, usePtr_, array, arrayIndex, Capacity - usePtr_);
                Array.Copy(buffer_, 0, array, arrayIndex + (Capacity - usePtr_), fillPtr_);
            }
        }

        public bool Remove(T item)
        {
            if (IsEmpty)
                return false;

            int index = -1;

            if (usePtr_ < fillPtr_)
            {
                for (int i = usePtr_; i < fillPtr_; ++i)
                {
                    if (buffer_[i].Equals(item))
                    {
                        index = i;
                        break;
                    }
                }

                if (index != -1)
                {
                    for (int i = index; i < fillPtr_ - 1; ++i)
                        buffer_[i] = buffer_[i + 1];
                }
            }
            else
            {
                for (int i = usePtr_; i < buffer_.Length; ++i)
                {
                    if (buffer_[i].Equals(item))
                    {
                        index = i;
                        break;
                    }
                }

                if (index != -1)
                {
                    for (int i = index; i < buffer_.Length - 1; ++i)
                        buffer_[i] = buffer_[i + 1];
                }
                else
                {
                    for (int i = 0; i < fillPtr_; ++i)
                    {
                        if (buffer_[i].Equals(item))
                        {
                            index = i;
                            break;
                        }
                    }

                    if (index != -1)
                    {
                        for (int i = index; i < fillPtr_ - 1; ++i)
                            buffer_[i] = buffer_[i + 1];
                    }
                }
            }

            if (index != -1)
            {
                Count -= 1;
                usePtr_ = (usePtr_ + 1) % Capacity;
                return true;
            }
            else
            {
                return false;
            }
        }
        #endregion

        #region IEnumerator<T>
        public IEnumerator<T> GetEnumerator()
        {
            return new Enumerator(this);
        }
        #endregion

        #region IEnumerable
        IEnumerator IEnumerable.GetEnumerator()
        {
            return new Enumerator(this);
        }
        #endregion

        #region Enumerator
        public struct Enumerator : IEnumerator<T>, IEnumerator
        {
            internal Enumerator(CircularBuffer<T> buffer)
            {
                buffer_ = buffer;
                index_ = -1;
                current_ = new T(); // default!
            }

            public T Current
            {
                get
                {
                    if (index_ < 0)
                        ThrowEnumerationNotStartedOrEnded();

                    return current_;
                }
            }

            object IEnumerator.Current
            {
                get
                {
                    return Current;
                }
            }

            public void Dispose()
            {
                index_ = -2;
                current_ = new T();
            }

            public bool MoveNext()
            {
                if (index_ == -2)
                    return false;

                ++index_;

                if (index_ == buffer_.Count)
                {
                    index_ = -2;
                    current_ = new T();
                    return false;
                }

                current_ = buffer_.buffer_[(buffer_.usePtr_ + index_) % buffer_.Capacity];
                return true;
            }

            public void Reset()
            {
                index_ = -1;
                current_ = new T();
            }


            // Queue.cs
            private void ThrowEnumerationNotStartedOrEnded()
            {
                Debug.Assert(index_ == -1 || index_ == -2);
                throw new InvalidOperationException(
                    index_ == -1 ? "Enumeration not started" : "Enumeration ended");
            }

            private readonly CircularBuffer<T> buffer_;
            private int index_;
            private T current_;
        }
        #endregion

        public T this[int i]
        {
            get
            {
                if (i < 0 || i >= Count)
                    throw new IndexOutOfRangeException("i");

                return buffer_[(usePtr_ + i) % Capacity];
            }

            set
            {
                if (i < 0 || i >= Count)
                    throw new IndexOutOfRangeException("i");

                buffer_[(usePtr_ + i) % Capacity] = value;
            }
        }

        public int AddMany(T[] items, int offset, int count)
        {
            if (items == null)
                throw new ArgumentNullException("items");

            if (offset < 0 || count < 0)
                throw new ArgumentException("offset or count");

            if (count > items.Length - offset)
                count = items.Length - offset;

            if (count > Reserve)
                count = Reserve;

            if (count == 0)
                return 0;

            if (fillPtr_ <= Capacity - count)
            {
                Array.Copy(items, offset, buffer_, fillPtr_, count);
            }
            else
            {
                var emptySlotsAtEnd = Capacity - fillPtr_;
                var emptySlotsAtBegin = count - emptySlotsAtEnd;

                Array.Copy(items, 0, buffer_, fillPtr_, emptySlotsAtEnd);
                Array.Copy(items, emptySlotsAtEnd, buffer_, 0, emptySlotsAtBegin);
            }

            Count += count;
            fillPtr_ = (fillPtr_ + count) % Capacity;

            return count;
        }

        public T? Remove()
        {
            if (IsEmpty)
                return null;

            var item = buffer_[usePtr_];

            Count -= 1;
            usePtr_ = (usePtr_ + 1) % Capacity;
            return item;
        }

        public int RemoveMany(T[] items, int offset, int count)
        {
            if (items == null)
                throw new ArgumentNullException("items");

            if (offset < 0 || count < 0)
                throw new ArgumentException("offset or count");

            if (count > items.Length - offset)
                count = items.Length - offset;

            if (count > Count)
                count = Count;

            if (count == 0)
                return 0;

            if (usePtr_ <= Capacity - count)
            {
                Array.Copy(buffer_, usePtr_, items, offset, count);
            }
            else
            {
                var filledSlotsAtEnd = Capacity - usePtr_;
                var filledSlotsAtBegin = count - filledSlotsAtEnd;

                Array.Copy(buffer_, usePtr_, items, offset, filledSlotsAtEnd);
                Array.Copy(buffer_, 0, items, offset + filledSlotsAtEnd, filledSlotsAtBegin);
            }

            Count -= count;
            usePtr_ = (usePtr_ + count) % Capacity;

            return count;
        }

        public bool Overwrite
        {
            get;
            set;
        }
        = false;

        public int Capacity
        {
            get
            {
                return buffer_.Length;
            }
        }

        public int Reserve
        {
            get
            {
                return Capacity - Count;
            }
        }

        public bool IsEmpty
        {
            get
            {
                return Count == 0;
            }
        }

        public void Rotate(int pos)
        {
        }

        public override string ToString()
        {
            var sb = new StringBuilder();
            sb.Append('[');

            if (usePtr_ < fillPtr_)
            {
                for (int i = 0; i < usePtr_; ++i)
                    sb.Append("--, ");

                for (int i = usePtr_; i < fillPtr_; ++i)
                {
                    sb.Append(buffer_[i]);
                    sb.Append(", ");
                }

                for (int i = fillPtr_; i < buffer_.Length; ++i)
                    sb.Append("--, ");
            }
            else if (fillPtr_ < usePtr_)
            {
                for (int i = 0; i < fillPtr_; ++i)
                {
                    sb.Append(buffer_[i]);
                    sb.Append(", ");
                }

                for (int i = fillPtr_; i < usePtr_; ++i)
                    sb.Append("--, ");

                for (int i = usePtr_; i < buffer_.Length; ++i)
                {
                    sb.Append(buffer_[i]);
                    sb.Append(", ");
                }
            }
            else
            {
                if (IsEmpty)
                {
                    for (int i = 0; i < buffer_.Length; ++i)
                        sb.Append("--, ");
                }
                else
                {
                    for (int i = 0; i < buffer_.Length; ++i)
                    {
                        sb.Append(buffer_[i]);
                        sb.Append(", ");
                    }
                }
            }

            if (sb.Length > 3)
                sb.Length = sb.Length - 2;

            sb.Append(']');

            return sb.ToString();
        }

        private readonly T[] buffer_;
        private int fillPtr_ = 0;
        private int usePtr_ = 0;
    }
}


// References:
// http://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
// Operating Systems: Three Easy Pieces, P352
// https://github.com/michaeltyson/TPCircularBuffer
// https://github.com/boostorg/circular_buffer
// https://stackoverflow.com/questions/13275975/circularbuffer-highly-efficient-implementation-both-thread-safe-and-not-thread
// https://github.com/joaoportela/CircullarBuffer-CSharp
// https://github.com/xorxornop/RingBuffer
// Microsoft.Practices.EnterpriseLibrary.Caching.ProducerConsumerQueue
// System.Collections.Concurrent.BlockingCollection
// https://github.com/dotnet/corefx/blob/master/src/System.Collections/src/System/Collections/Generic/Queue.cs
// https://stackoverflow.com/questions/424669/how-do-i-overload-the-operator-in-c-sharp
// https://github.com/spazzarama/SharedMemory/blob/master/SharedMemory/CircularBuffer.cs
// Microsoft.Research.DynamicDataDisplay.Common.RingArray
// https://github.com/naudio/NAudio/blob/master/NAudio/Utils/CircularBuffer.cs
// [CircularBuffer highly efficient implementation (both thread-safe and not thread-safe)](https://stackoverflow.com/questions/13275975/circularbuffer-highly-efficient-implementation-both-thread-safe-and-not-thread)
// https://github.com/disruptor-net/Disruptor-net/blob/master/src/Disruptor/RingBuffer.cs
// [CircularBuffer - a first-in, first-out collection of objects using a fixed buffer](https://www.cyotek.com/blog/circularbuffer-a-first-in-first-out-collection-of-objects-using-a-fixed-buffer) - NuGet package: Cyotek CircularBuffer
// https://archive.codeplex.com/?p=circularbuffer
// https://github.com/nieltg/Collections.Generic.CircularBuffer
// https://github.com/embeddedartistry/embedded-resources/blob/master/examples/c/circular_buffer/circular_buffer.c
// [Creating a Circular Buffer in C and C++](https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/)
// https://github.com/cyotek/Cyotek.Collections.Generic.CircularBuffer
// https://github.com/MaskRay/ell/blob/master/ell/ringbuf.c
// https://github.com/Cinegy/TsDecoder/blob/master/Cinegy.TsDecoder/Buffers/RingBuffer.cs
// https://github.com/padenot/ringbuf.js
// https://github.com/jcurl/RJCP.DLL.BufferIO/blob/master/BufferIO/Buffer/CircularBuffer.cs
