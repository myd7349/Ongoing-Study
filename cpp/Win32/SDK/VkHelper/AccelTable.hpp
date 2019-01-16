#ifndef ACCEL_TABLE_HPP_
#define ACCEL_TABLE_HPP_

#include <limits>
#include <map>
#include <vector>

#include "KeySequence.h"


#ifdef _MSC_VER
# define FORCEINLINE __forceinline
#elif (defined(__GNUC__) && !defined(FORCEINLINE))
# define FORCEINLINE __attribute__((always_inline)) inline
#endif // _MSC_VER


FORCEINLINE int AccelTableGetCount(HACCEL hAccel)
{
    assert(hAccel != nullptr);
    return CopyAcceleratorTable(hAccel, nullptr, 0);
}


FORCEINLINE int AccelTableGetEntries(HACCEL hAccel, ACCEL *pEntries, int iCount)
{
    assert((pEntries != nullptr && iCount > 0) || (pEntries == nullptr && iCount == 0));
    return CopyAcceleratorTable(hAccel, pEntries, iCount);
}


using cmd_t = decltype(ACCEL::cmd);

const cmd_t InvalidCommandId = std::numeric_limits<cmd_t>::max();


class AccelTable
{
public:
    using AccelTableImpl = std::map<cmd_t, KeySequence>;
    using Iterator = AccelTableImpl::iterator;
    using ConstIterator = AccelTableImpl::const_iterator;

    explicit AccelTable(HACCEL hAccel = nullptr)
    {
        if (hAccel != nullptr)
        {
            int count = AccelTableGetCount(hAccel);
            if (count > 0)
            {
                std::vector<ACCEL> entries(count);
                Verify(AccelTableGetEntries(hAccel, entries.data(), count) == count);

                for (const auto &accel : entries)
                {
                    KeySequence sequence(accel);

                    auto it = table_.find(accel.cmd);
                    if (it != table_.cend())
                    {
                        it->second = sequence;
                    }
                    else
                    {
                        table_[accel.cmd] = sequence;
                    }
                }
            }
        }
    }

    KeySequence &operator[](cmd_t cmd)
    {
        assert(cmd != InvalidCommandId);
        return table_[cmd];
    }

    /*
    C++ Primer, 5th Edition, 14.5. Subscript Operator
    >If a class has a subscript operator, it usually should
    define two versions: one that returns a plain reference
    and the other that is a const member and returns a
    reference to const.

    std::map doesn't have a const overload of `operator[]`.

    https://stackoverflow.com/questions/1474894/why-isnt-the-operator-const-for-stl-maps

    const KeySequence &operator[](cmd_t cmd) const
    {
        assert(cmd != InvalidCommandId);
        return table_[cmd];
    }
    */

    ConstIterator Find(cmd_t cmd) const
    {
        assert(cmd != InvalidCommandId);
        return table_.find(cmd);
    }

    Iterator Find(cmd_t cmd)
    {
        assert(cmd != InvalidCommandId);
        return table_.find(cmd);
    }

    ConstIterator Find(const KeySequence &sequence) const
    {
        assert(sequence.IsValid());

        for (auto it = cbegin(); it != cend(); ++it)
        {
            if (it->second == sequence)
                return it;
        }

        return cend();
    }

    Iterator Find(const KeySequence &sequence)
    {
        assert(sequence.IsValid());

        for (auto it = begin(); it != end(); ++it)
        {
            if (it->second == sequence)
                return it;
        }

        return end();
    }

    ConstIterator cbegin() const
    {
        return table_.cbegin();
    }

    ConstIterator cend() const
    {
        return table_.cend();
    }

    Iterator begin()
    {
        return table_.begin();
    }

    Iterator end()
    {
        return table_.end();
    }

    HACCEL CreateAcceleratorTable() const
    {
        std::vector<ACCEL> entries;
        entries.reserve(table_.size());

        for (const auto &kv : table_)
        {
            ACCEL accel = kv.second.ToAccel();
            accel.cmd = kv.first;

            entries.push_back(accel);
        }

        return ::CreateAcceleratorTable(entries.data(), static_cast<int>(entries.size()));
    }

private:
    AccelTableImpl table_;
};

#endif // ACCEL_TABLE_HPP_
