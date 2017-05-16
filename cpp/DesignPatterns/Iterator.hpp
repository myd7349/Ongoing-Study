// 2017-04-26T17:45+08:00
#pragma once

#include <stdexcept>

template <typename T>
class Iterator
{
public:
    virtual void First() = 0;
    virtual void MoveNext() = 0;
    virtual bool IsDone() = 0;
    virtual T Current() = 0;
};

class StopIterationError : public std::runtime_error
{
public:
    StopIterationError() : std::runtime_error("StopIteration") {}
    StopIterationError(const char *msg) : std::runtime_error(msg) {}
    StopIterationError(const std::string &msg) : std::runtime_error(msg) {}
};

template <typename T>
class NullIterator : public Iterator<T>
{
public:
    virtual void First() {}
    virtual void MoveNext() {}
    virtual bool IsDone() { return true; }
    virtual T Current() { throw StopIterationError(); }
};

template <typename Container, typename T>
class ContainerIterator : public Iterator<T>
{
public:
    ContainerIterator(Container c) : container_(c) {} // TODO: The container is copied

    virtual void First()
    {
        it_ = container_.begin();
    }

    virtual void MoveNext()
    {
        ++it_;
    }

    virtual bool IsDone()
    {
        return it_ == container_.end();
    }

    virtual T Current()
    {
        try
        {
            return *it_;
        }
        catch (...)
        {
            throw StopIterationError();
        }
    }

private:
    Container container_;
    typename Container::iterator it_;
};
