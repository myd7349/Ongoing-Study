#pragma once

class Handle;

class UseCount
{
public:
    UseCount()
        : use_count_(new int(1))
    {
    }

    UseCount(const UseCount &uc)
        : use_count_(uc.use_count_)
    {
        ++*use_count_;
    }

    ~UseCount()
    {
        if (--*use_count_ == 0)
            delete use_count_;
    }

    int use_count() const
    {
        return *use_count_;
    }

    bool unique() const
    {
        return use_count() == 1;
    }

    bool reattach(const UseCount &uc)
    {
        ++*uc.use_count_;
        if (--*use_count_ == 0)
        {
            delete use_count_;
            use_count_ = uc.use_count_;
            return true;
        }

        use_count_ = uc.use_count_;
        return false;
    }

    bool makeonly()
    {
        if (*use_count_ == 1)
            return false;

        --*use_count_;
        use_count_ = new int(1);
        return true;
    }

private:
    int *use_count_;
};


// References:
// Ruminations on C++, Ch7
