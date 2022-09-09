// ReadOnlyDictionary.cs license information:
// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;

namespace Common
{
    [DebuggerDisplay("Count = {Count}")]
    public class EnumDictionary<TKey, TValue> : IDictionary<TKey, TValue>, IDictionary
        where TKey : struct
    {
        public EnumDictionary(TValue initial = default(TValue))
        {
            var length = EnumKeys.Select(x => Convert.ToInt32(x)).Max() + 1;
            store_ = new TValue[length];

            if (!EqualityComparer<TValue>.Default.Equals(initial, default(TValue)))
                ArrayHelper.Fill(store_, initial);
        }

        public ICollection<TKey> Keys => EnumKeys;

        public ICollection<TValue> Values => store_;

        public bool ContainsKey(TKey key)
        {
            return Enum.IsDefined(typeof(TKey), key);
        }

        public bool TryGetValue(TKey key, out TValue value)
        {
            if (ValidateKey(key, out int internalKey))
            {
                value = store_[internalKey];
                return true;
            }
            else
            {
                value = default(TValue);
                return false;
            }
        }

        public TValue this[TKey key]
        {
            get
            {
                if (ValidateKey(key, out int internalKey))
                    return store_[internalKey];

                throw new KeyNotFoundException($"{key}");
            }

            set
            {
                if (ValidateKey(key, out int internalKey))
                    store_[internalKey] = value;
                else
                    throw new KeyNotFoundException($"{key}");
            }
        }

        public int Count => store_.Length;

        void IDictionary<TKey, TValue>.Add(TKey key, TValue value)
        {
            throw new NotSupportedException();
        }

        bool IDictionary<TKey, TValue>.Remove(TKey key)
        {
            throw new NotSupportedException();
        }

        bool ICollection<KeyValuePair<TKey, TValue>>.Contains(KeyValuePair<TKey, TValue> item)
        {
            return ContainsKey(item.Key) &&
                EqualityComparer<TValue>.Default.Equals(item.Value, this[item.Key]);
        }

        void ICollection<KeyValuePair<TKey, TValue>>.CopyTo(KeyValuePair<TKey, TValue>[] array, int arrayIndex)
        {
            ValidateCopyToArguments(Count, array, arrayIndex);

            int i = 0;
            for (int j = arrayIndex; j < array.Length; ++j)
                array[j] = new KeyValuePair<TKey, TValue>(
                    (TKey)(object)i, // (TKey)i
                    store_[i]);
        }

        bool ICollection<KeyValuePair<TKey, TValue>>.IsReadOnly => throw new NotSupportedException();

        void ICollection<KeyValuePair<TKey, TValue>>.Add(KeyValuePair<TKey, TValue> item)
        {
            throw new NotSupportedException();
        }

        void ICollection<KeyValuePair<TKey, TValue>>.Clear()
        {
            throw new NotSupportedException();
        }

        bool ICollection<KeyValuePair<TKey, TValue>>.Remove(KeyValuePair<TKey, TValue> item)
        {
            throw new NotSupportedException();
        }

        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
        {
            return new Enumerator(this, Enumerator.KeyValuePair);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new Enumerator(this, Enumerator.KeyValuePair);
        }

        void IDictionary.Add(object key, object value)
        {
            throw new NotSupportedException();
        }

        void IDictionary.Clear()
        {
            throw new NotSupportedException();
        }

        bool IDictionary.Contains(object key)
        {
            return IsCompatible<TKey>(key) && ContainsKey((TKey)key);
        }

        IDictionaryEnumerator IDictionary.GetEnumerator()
        {
            return new Enumerator(this, Enumerator.DictEntry);
        }

        bool IDictionary.IsFixedSize => true;

        bool IDictionary.IsReadOnly => throw new NotSupportedException();

        ICollection IDictionary.Keys => EnumKeys;

        void IDictionary.Remove(object key)
        {
            throw new NotSupportedException();
        }

        ICollection IDictionary.Values => store_;

        object IDictionary.this[object key]
        {
            get
            {
                if (!IsCompatible<TKey>(key))
                    throw new KeyNotFoundException($"{key}");

                if (TryGetValue((TKey)key, out TValue value))
                    return value;

                throw new KeyNotFoundException($"{key}");
            }

            set
            {
                if (!IsCompatible<TKey>(key))
                    throw new KeyNotFoundException($"{key}");

                if (!IsCompatible<TValue>(value))
                    throw new ArgumentException(nameof(value));

                if (ValidateKey((TKey)key, out int internalKey))
                    store_[internalKey] = (TValue)value;
                else
                    throw new KeyNotFoundException($"{key}");
            }
        }

        void ICollection.CopyTo(Array array, int arrayIndex)
        {
            ValidateCopyToArguments(Count, array, arrayIndex);

            if (array is KeyValuePair<TKey, TValue>[] pairs)
            {
                // Simplify?
                ((ICollection<KeyValuePair<TKey, TValue>>)this).CopyTo(pairs, arrayIndex);
            }
            else
            {
                if (array is DictionaryEntry[] dictEntryArray)
                {
                    for (int i = 0; i < store_.Length; ++i)
                    {
                        dictEntryArray[arrayIndex++] = new DictionaryEntry(
                            (TKey)(object)i,
                            store_[i]);
                    }
                }
                else
                {
                    object[] objects = array as object[];
                    if (objects == null)
                        throw new ArgumentException("Incompatible array type.", nameof(array));

                    try
                    {
                        for (int i = 0; i < store_.Length; ++i)
                        {
                            objects[arrayIndex++] = new KeyValuePair<TKey, TValue>(
                                (TKey)(object)i,
                                store_[i]);
                        }
                    }
                    catch (ArrayTypeMismatchException)
                    {
                        throw new ArgumentException("Incompatible array type.", nameof(array));
                    }
                }
            }
        }

        bool ICollection.IsSynchronized => false;

        object ICollection.SyncRoot => this;

        public struct Enumerator : IEnumerator<KeyValuePair<TKey, TValue>>, IDictionaryEnumerator
        {
            internal Enumerator(EnumDictionary<TKey, TValue> dictionary, int getEnumeratorRetType)
            {
                dictionary_ = dictionary;
                index_ = 0;
                current_ = default(KeyValuePair<TKey, TValue>);
                getEnumeratorRetType_ = getEnumeratorRetType;
            }

            public bool MoveNext()
            {
                // Use unsigned comparison since we set index to dictionary.count+1 when the enumeration ends.
                // dictionary.count+1 could be negative if dictionary.count is int.MaxValue
                // TODO:
                // https://github.com/dotnet/runtime/blob/main/src/libraries/System.Private.CoreLib/src/System/Collections/Generic/Dictionary.cs
                // while ((uint)_index < (uint)_dictionary._count)
                // {
                //     ...
                // }
                // Why?
                if ((uint)index_ < (uint)dictionary_.store_.Length)
                {
                    var kv = new KeyValuePair<TKey, TValue>(
                        (TKey)(object)index_,
                        dictionary_.store_[index_]);

                    index_++;

                    current_ = kv;

                    return true;
                }
                else
                {
                    index_ = dictionary_.store_.Length + 1;
                    current_ = default(KeyValuePair<TKey, TValue>);
                    return false;
                }
            }

            public KeyValuePair<TKey, TValue> Current => current_;

            public void Dispose()
            {
            }

            object IEnumerator.Current
            {
                get
                {
                    if (index_ == 0 || (index_ == dictionary_.store_.Length + 1))
                        throw new InvalidOperationException();

                    if (getEnumeratorRetType_ == DictEntry)
                        return new DictionaryEntry(current_.Key, current_.Value);

                    return new KeyValuePair<TKey, TValue>(current_.Key, current_.Value);
                }
            }

            void IEnumerator.Reset()
            {
                index_ = 0;
                current_ = default(KeyValuePair<TKey, TValue>);
            }

            DictionaryEntry IDictionaryEnumerator.Entry
            {
                get
                {
                    if (index_ == 0 || (index_ == dictionary_.store_.Length + 1))
                        throw new InvalidOperationException();

                    return new DictionaryEntry(current_.Key, current_.Value);
                }
            }

            object IDictionaryEnumerator.Key
            {
                get
                {
                    if (index_ == 0 || (index_ == dictionary_.store_.Length + 1))
                        throw new InvalidOperationException();

                    return current_.Key;
                }
            }

            object IDictionaryEnumerator.Value
            {
                get
                {
                    if (index_ == 0 || (index_ == dictionary_.store_.Length + 1))
                        throw new InvalidOperationException();

                    return current_.Value;
                }
            }

            internal const int DictEntry = 1;
            internal const int KeyValuePair = 2;

            private EnumDictionary<TKey, TValue> dictionary_;
            private int index_;
            private KeyValuePair<TKey, TValue> current_;
            private readonly int getEnumeratorRetType_;
        }

        private static bool IsCompatible<T>(object key)
        {
            if (key == null)
                throw new ArgumentNullException(nameof(key));

            return key is T;
        }

        private bool ValidateKey(TKey key, out int internalKey)
        {
            internalKey = Convert.ToInt32(key); // (int)key

#if false
            return internalKey >= 0 && internalKey < store_.Length;
#else
            return Enum.IsDefined(typeof(TKey), key);
#endif
        }

        // https://github.com/dotnet/runtime/blob/main/src/libraries/System.ObjectModel/src/System/Collections/CollectionHelpers.cs
        private static void ValidateCopyToArguments(int sourceCount, Array array, int arrayIndex)
        {
            if (array == null)
                throw new ArgumentNullException(nameof(array));

            if (array.Rank != 1)
                throw new ArgumentException("Rand of array should be 1.", nameof(array));

            if (array.GetLowerBound(0) != 0)
                throw new ArgumentException("Lower bound of array rand 0 should be 0.", nameof(array));

            if (arrayIndex < 0 || arrayIndex > array.Length)
                throw new ArgumentOutOfRangeException(nameof(arrayIndex));

            if (array.Length - arrayIndex < sourceCount)
                throw new ArgumentException("No enough space.", nameof(array));
        }

        private static readonly ReadOnlyCollection<TKey> EnumKeys =
            new ReadOnlyCollection<TKey>((TKey[])Enum.GetValues(typeof(TKey)));
        private TValue[] store_;
    }
}


// References:
// https://github.com/dotnet/runtime/blame/main/src/libraries/System.Private.CoreLib/src/System/Collections/ObjectModel/ReadOnlyDictionary.cs
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.ObjectModel/src/System/Collections/CollectionHelpers.cs
// [Dictionary with initial capacity](https://stackoverflow.com/questions/11907809/dictionary-with-initial-capacity)
// [A fixed size Dictionary with substitution priority](https://stackoverflow.com/questions/17675406/a-fixed-size-dictionary-with-substitution-priority)
// [Fixed size dictionary to achieve performance goals](https://codereview.stackexchange.com/questions/158339/fixed-size-dictionary-to-achieve-performance-goals)
// https://github.com/aegoroff/logviewer/blob/develop/logviewer.logic/support/FixedSizeDictionary.cs
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Collections.Immutable/src/System/Collections/Immutable/DictionaryEnumerator.cs
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Private.CoreLib/src/System/Collections/Generic/Dictionary.cs
