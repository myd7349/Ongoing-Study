// 2017-04-26 17:40
#pragma once

#include <functional>

#include "Iterable.hpp"

class Component;

typedef std::shared_ptr<Component> SharedComponentPtr;

typedef std::shared_ptr<Iterator<SharedComponentPtr>> ComponentIterator;

class Component
{
public:
    virtual ~Component() {};

    virtual void Add(SharedComponentPtr child) {}
    virtual void Remove(SharedComponentPtr child) {}
    virtual void RemoveIf(SharedComponentPtr child, std::function<bool(SharedComponentPtr)> pred) {}
    virtual void Clear() {}
    virtual ComponentIterator CreateIterator(TraversalKind traversalKind = None) { return std::make_shared<NullIterator<SharedComponentPtr>>(); }
};