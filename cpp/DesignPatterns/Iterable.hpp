// 2017-04-26T17:45+08:00
#pragma once

#include <functional>
#include <memory>

#include "Iterator.hpp"

enum TraversalKind
{
    None,
    BFS,
    DFS,
};

template <typename T>
class Iterable
{
public:
    virtual std::shared_ptr<Iterator<T>> CreateIterator(TraversalKind traversalKind, std::function<bool(T t)> selector) = 0;
};