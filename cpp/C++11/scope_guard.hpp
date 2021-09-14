#pragma once

#include <functional>


class scope_guard
{
public:
    template<class Callable>
    scope_guard(Callable&& undo_func)
    try
        : f(std::forward<Callable>(undo_func))
    {
    }
    catch (...)
    {
        undo_func();
        throw;
    }

    scope_guard(scope_guard&& other) noexcept
        : f(std::move(other.f))
    {
        other.f = nullptr;
    }

    ~scope_guard()
    {
        if (f)
            f(); // must not throw
    }

    void dismiss() noexcept
    {
        f = nullptr;
    }

    scope_guard(const scope_guard&) = delete;
    void operator = (const scope_guard&) = delete;

private:
    std::function<void()> f;
};


// References:
// https://docs.microsoft.com/en-us/cpp/parallel/concrt/walkthrough-removing-work-from-a-user-interface-thread?view=msvc-160
// https://en.cppreference.com/w/cpp/experimental/scope_exit
// https://github.com/SergiusTheBest/ScopeExit
// [The simplest and neatest c++11 ScopeGuard](https://stackoverflow.com/questions/10270328/the-simplest-and-neatest-c11-scopeguard)
// https://github.com/ricab/scope_guard
// [What is ScopeGuard in C++?](https://stackoverflow.com/questions/31365013/what-is-scopeguard-in-c)
