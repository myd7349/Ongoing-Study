#pragma once

#include <cstddef>
#include <functional>
#include <exception>
#include <thread>
#include <tuple>
#include <utility>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
#else
# include <pthread.h>
# error Not implemented!
#endif


struct once_flag
{
    once_flag() = default;

    once_flag(const once_flag &) = delete;
    once_flag &operator=(const once_flag &) = delete;

#ifdef _WIN32
    INIT_ONCE once_ = INIT_ONCE_STATIC_INIT;
#else
    pthread_once_t once_ = PTHREAD_ONCE_INIT;
#endif
};


template <typename... TArgs, std::size_t... Indices>
inline auto invoke_stored_explicit(std::tuple<TArgs...>&& tuple, std::index_sequence<Indices...>)
    -> decltype(std::invoke(std::get<Indices>(std::move(tuple))...))
{
    // invoke() a tuple with explicit parameter ordering
    return std::invoke(std::get<Indices>(std::move(tuple))...);
}


template <typename... TArgs>
inline auto invoke_stored(std::tuple<TArgs...>&& tuple)
    -> decltype(invoke_stored_explicit(std::move(tuple), std::index_sequence_for<TArgs...>()))
{
    // invoke() a tuple
    return invoke_stored_explicit(std::move(tuple), std::index_sequence_for<TArgs...>());
}


#ifdef _WIN32
// PINIT_ONCE_FN is defined as:
// BOOL CALLBACK InitOnceCallback(
//     __inout      PINIT_ONCE InitOnce,
//     __inout_opt  PVOID Parameter,
//     __out_opt    PVOID* Context
// );

template<typename TArgsTuple, typename TArgsSeq, std::size_t Indices>
int __stdcall call_once_impl(void *, void *pv, void **)
{
    auto args_tuple_ptr = static_cast<TArgsTuple *>(pv);

    try
    {
        invoke_stored_explicit(std::move(*args_tuple_ptr), TArgsSeq());
        return 1;
    }
    catch (...)
    {
        auto &exc_ref = std::get<Indices>(*args_tuple_ptr);
        exc_ref = std::current_exception();
        return 0;
    }
}
#endif


template<typename TFunc, typename... TArgs>
inline void call_once(once_flag &flag, TFunc&& func, TArgs&&... args)
{
    using ArgsTuple = std::tuple<TFunc&&, TArgs&&..., std::exception_ptr &>;
    using ArgsSeq = std::make_index_sequence<1 + sizeof...(TArgs)>;

    std::exception_ptr exc_ptr;
    ArgsTuple args_tuple(std::forward<TFunc>(func), std::forward<TArgs>(args)..., exc_ptr);

#ifdef _WIN32
    auto call_once_func_ptr = &call_once_impl<ArgsTuple, ArgsSeq, 1 + sizeof...(TArgs)>;

    if (::InitOnceExecuteOnce(
        &flag.once_,
        reinterpret_cast<PINIT_ONCE_FN>(call_once_func_ptr),
        std::addressof(args_tuple),
        nullptr))
        return;
#else
    // PThreads has a function named pthread_once which accepts a callback of type:
    //    void (*init_routine)(void)
    // so it is not possible to pass some extra arguments to this function.
#endif

    if (exc_ptr)
        std::rethrow_exception(exc_ptr);
}


// References:
// C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\crt\src\stl\xonce.cpp
// https://github.com/nanomsg/nanomsg/blob/master/src/utils/once.c
// https://stackoverflow.com/questions/21740871/passing-function-as-argument-to-pthread-once
// https://codereview.stackexchange.com/questions/117468/stdonce-flag-and-stdcall-once-implementation
// https://code.woboq.org/userspace/glibc/nptl/pthread_once.c.html
// https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/ptonce.htm
// https://linux.die.net/man/3/pthread_once
// https://codereview.stackexchange.com/questions/117468/stdonce-flag-and-stdcall-once-implementation
// boost/thread/once.hpp
// https://stackoverflow.com/questions/40639978/c11-thread-safe-singleton-using-lambda-and-call-once-main-function-g-clan
// [pthread_once with parameter](https://groups.google.com/forum/m/#!topic/comp.programming.threads/AX2YtBN6jhw)
// https://github.com/nemequ/portable-snippets/tree/master/once
