// 2017-04-26 17:40
#pragma once

#include <list>

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
    virtual void RemoveIf(ComponentSelector selector) {}
    virtual void Clear() {}
    virtual ComponentIterator CreateIterator(TraversalKind traversalKind = None, ComponentSelector selector = ComponentSelector()) { return std::make_shared<NullIterator<SharedComponentPtr>>(); }

    // TODO: What if we changed name of this function to `CreateIterator`?
    // TODO: This implementation is ugly, fix it!
    template <typename T>
    /*virtual*/ // C2898: member function templates cannot be virtual
    std::shared_ptr<Iterator<std::shared_ptr<T>>> CreateTypedIterator(
        TraversalKind traversalKind = None,
        std::function<bool(std::shared_ptr<T>)> selector = std::function<bool(std::shared_ptr<T>)>())
    {
        ComponentSelector typeSelector = [](SharedComponentPtr component)->bool
        {
            return dynamic_cast<T *>(component.get()) != nullptr;
        };

        std::list<std::shared_ptr<T>> theOnes;

        ComponentIterator iterator = CreateIterator(traversalKind, typeSelector);
        iterator->First();

        while (!iterator->IsDone())
        {
            std::shared_ptr<T> current = std::dynamic_pointer_cast<T>(iterator->Current());
            if (!selector || selector(current))
                theOnes.push_back(current);

            iterator->MoveNext();
        }

        return std::make_shared<ContainerIterator<std::list<std::shared_ptr<T>>, std::shared_ptr<T>>>(theOnes);
    }
};
