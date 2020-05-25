#pragma once

#include "point.hpp"
#include "use_count.hpp"


class Handle
{
public:
    Handle(int xv = 0, int yv = 0)
        : p_(new Point(xv, yv))
    {
    }

    Handle(const Point &pt)
        : p_(new Point(pt))
    {
    }
    
    virtual ~Handle()
    {
        if (use_count_.unique())
            delete p_;
    }

    Handle &operator=(const Handle &handle)
    {
        if (use_count_.reattach(handle.use_count_))
            delete p_;

        p_ = handle.p_;
        return *this;
    }

    int x() const
    {
        return p_->x();
    }

    int y() const
    {
        return p_->y();
    }

    int use_count() const
    {
        return use_count_.use_count();
    }

    virtual Handle &x(int xv) = 0;
    virtual Handle &y(int yv) = 0;

    //Point *operator->();

protected:
    Point *p_;
    UseCount use_count_;
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
        p_->x(xv);
        return *this;
    }

    Handle &y(int yv)
    {
        p_->y(yv);
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
        if (use_count_.makeonly())
            p_ = new Point(*p_);

        p_->x(xv);
        return *this;
    }

    Handle &y(int yv)
    {
        if (use_count_.makeonly())
            p_ = new Point(*p_);

        p_->y(yv);
        return *this;
    }
};


// References:
// https://stackoverflow.com/questions/166033/what-do-value-semantics-and-pointer-semantics-mean
// Ruminations on C++, Ch7
