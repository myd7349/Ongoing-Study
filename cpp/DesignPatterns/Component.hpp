// 2017-04-26 17:40
#pragma once

#include "Iterable.hpp"

class Component;

typedef std::shared_ptr<Component> SharedComponentPtr;

typedef std::shared_ptr<Iterator<SharedComponentPtr>> ComponentIterator;

typedef std::function<bool(SharedComponentPtr t)> ComponentSelector;

class Component : public Iterable<SharedComponentPtr>
{
public:
    virtual ~Component() {}

    virtual void Add(SharedComponentPtr child) {}
    virtual void Remove(SharedComponentPtr child) {}
    virtual void RemoveIf(SharedComponentPtr child, ComponentSelector selector) {}
    virtual void Clear() {}
    virtual ComponentIterator CreateIterator(TraversalKind traversalKind = None, ComponentSelector selector = ComponentSelector()) { return std::make_shared<NullIterator<SharedComponentPtr>>(); }
};