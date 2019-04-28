#pragma once

#include "upoint.hpp"


class Handle
{
public:
    Handle(int xv = 0, int yv = 0)
        : p_(new UPoint(xv, yv))
    {
    }

    Handle(const Point &pt)
        : p_(new UPoint(pt))
    {
    }

    Handle(const Handle &handle)
        : p_(handle.p_)
    {
        ++p_->use_count_;
    }
    
    virtual ~Handle()
    {
        if (--p_->use_count_ == 0)
            delete p_;
    }

    Handle &operator=(const Handle &handle)
    {
        ++handle.p_->use_count_;
        
        if (--p_->use_count_ == 0)
            delete p_;

        p_ = handle.p_;
        return *this;
    }

    int x() const
    {
        return p_->pt_.x();
    }

    int y() const
    {
        return p_->pt_.y();
    }

    int use_count() const
    {
        return p_->use_count_;
    }

    virtual Handle &x(int xv) = 0;
    virtual Handle &y(int yv) = 0;

    //Point *operator->();

protected:
    UPoint *p_;
};


class HandlePtr : public Handle
{
public:
    using Handle::Handle;
    using Handle::x;
    using Handle::y;

    // Pointer semantics
    Handle &x(int xv)
    {
        p_->pt_.x(xv);
        return *this;
    }

    Handle &y(int yv)
    {
        p_->pt_.y(yv);
        return *this;
    }
};


class HandleValue : public Handle
{
public:
    using Handle::Handle;
    using Handle::x;
    using Handle::y;

    // Value semantics
    // Copy-on-write
    Handle &x(int xv)
    {
        copy_on_write();
        p_->pt_.x(xv);

        return *this;
    }

    Handle &y(int yv)
    {
        copy_on_write();
        p_->pt_.y(yv);

        return *this;
    }

private:
    void copy_on_write()
    {
        if (p_->use_count_ != 1)
        {
            --p_->use_count_;
            p_ = new UPoint(p_->pt_);
        }
    }
};


// References:
// https://stackoverflow.com/questions/166033/what-do-value-semantics-and-pointer-semantics-mean
// Ruminations on C++, Ch6
