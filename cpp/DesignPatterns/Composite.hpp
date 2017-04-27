// 2017-04-26 17:45
#pragma once

#include <cassert>
#include <deque>
#include <queue>
#include <stack>

#include "Component.hpp"

class Composite : public Component
{
public:
    typedef std::deque<SharedComponentPtr> Children;

    // ??
    class CompositeElementIterator : public Iterator<SharedComponentPtr>
    {
    public:
        CompositeElementIterator(Composite &composite)
            : composite_(composite), isDone_(true)
        {
        }
        
        virtual void First()
        {
            it_ = composite_.children_.begin();
            isDone_ = it_ == composite_.children_.end();
        }
        
        virtual void MoveNext()
        {
            if (!isDone_)
            {
                ++it_;
                isDone_ = it_ == composite_.children_.end();
            }
        }
        
        virtual bool IsDone()
        {
            return isDone_;
        }
        
        virtual SharedComponentPtr Current()
        {
            if (isDone_)
                throw StopIterationError();

            return *it_;
        }

    private:
        Composite &composite_;
        Children::iterator it_;
        bool isDone_;
    };

    class CompositeElementRecursiveBFSIterator : public Iterator<SharedComponentPtr>
    {
    public:
        CompositeElementRecursiveBFSIterator(Composite &composite)
            : composite_(composite)
        {
        }
        
        virtual void First()
        {
            // clear the queue
            std::queue<SharedComponentPtr> emptyQueue;
            queue_.swap(emptyQueue);
            
            UpdateCurrentIterator(composite_);
        }
        
        virtual void MoveNext()
        {
            if (!current_->IsDone())
            {
                current_->MoveNext();
            }

            while (!queue_.empty() && current_->IsDone())
            {
                UpdateCurrentIterator(*queue_.front());
                queue_.pop();
            }
        }
        
        virtual bool IsDone()
        {
            return !current_ || current_->IsDone();
        }
        
        virtual SharedComponentPtr Current()
        {
            if (IsDone())
                throw StopIterationError();

            return current_->Current();
        }

    private:
        void UpdateCurrentIterator(Component &component)
        {
            assert(!current_ || current_->IsDone());

            // the first shoot
            current_ = component.CreateIterator(None);
            for (current_->First(); !current_->IsDone(); current_->MoveNext())
                queue_.push(current_->Current());

            current_->First(); // reset iterator
        }

        Composite &composite_;
        std::queue<SharedComponentPtr> queue_;
        ComponentIterator current_;
    };

    class CompositeElementRecursiveDFSIterator : public Iterator<SharedComponentPtr>
    {
    public:
        CompositeElementRecursiveDFSIterator(Composite &composite)
            : composite_(composite)
        {
        }
        
        virtual void First()
        {
            // clear the stack
            std::stack<ComponentIterator> emptyStack;
            unvisited_.swap(emptyStack);

            ComponentIterator iterator = composite_.CreateIterator(None);
            iterator->First();

            unvisited_.push(iterator);
        }
        
        virtual void MoveNext()
        {
            if (!unvisited_.empty())
            {
                ComponentIterator topIterator = unvisited_.top();
                if (!topIterator->IsDone())
                {
                    ComponentIterator iterator = topIterator->Current()->CreateIterator();
                    iterator->First();
                    unvisited_.push(iterator);
                    topIterator->MoveNext();
                }
            }

            while (!unvisited_.empty() && unvisited_.top()->IsDone())
            {
                unvisited_.pop();
            }
        }
        
        virtual bool IsDone()
        {
            return unvisited_.empty() || (unvisited_.size() == 1 && unvisited_.top()->IsDone());
        }
        
        virtual SharedComponentPtr Current()
        {
            if (IsDone())
                throw StopIterationError();

            return unvisited_.top()->Current();
        }

    private:
        Composite &composite_;
        std::stack<ComponentIterator> unvisited_;
    };

    class CompositeElementSelectorIterator : public Iterator<SharedComponentPtr>
    {
    public:
        CompositeElementSelectorIterator(ComponentIterator iterator, std::function<bool(SharedComponentPtr)> selector)
            : iterator_(iterator), selector_(selector)
        {
        }

        virtual void First()
        {
            iterator_->First();
            SkipUntile();
        }

        virtual void MoveNext()
        {
            iterator_->MoveNext();
            SkipUntile();
        }

        virtual bool IsDone()
        {
            return iterator_->IsDone();
        }

        virtual SharedComponentPtr Current()
        {
            return iterator_->Current();
        }

    private:
        void SkipUntile()
        {
            if (selector_)
            {
                while (!iterator_->IsDone())
                {
                    if (selector_(iterator_->Current()))
                        break;

                    iterator_->MoveNext();
                }
            }
        }

        ComponentIterator iterator_;
        std::function<bool(SharedComponentPtr)> selector_;
    };

    virtual void Add(SharedComponentPtr child)
    {
        assert(child);

        if (!child)
            return;

        children_.push_back(child);
    }

    virtual void Remove(SharedComponentPtr child)
    {
        RemoveIf(child, [child](SharedComponentPtr e) { return e == child; });
    }

    virtual void RemoveIf(SharedComponentPtr child, ComponentSelector selector)
    {
        assert(child);
        assert(selector);

        for (Children::iterator it = children_.begin(); it != children_.end(); )
        {
            if (selector(*it))
                children_.erase(it++);
            else
                ++it;
        }
    }

    virtual void Clear()
    {
        children_.clear();
    }

    virtual ComponentIterator CreateIterator(TraversalKind traversalKind = None, ComponentSelector selector = ComponentSelector())
    {
        ComponentIterator iterator = CreateIteratorInternal(traversalKind);
        if (selector)
            return std::make_shared<CompositeElementSelectorIterator>(iterator, selector);
        else
            return iterator;
    }

    ComponentIterator CreateIteratorInternal(TraversalKind traversalKind)
    {
        switch (traversalKind)
        {
        case BFS:
            return std::make_shared<CompositeElementRecursiveBFSIterator>(*this);
            break;
        case DFS:
            return std::make_shared<CompositeElementRecursiveDFSIterator>(*this);
            break;
        default:
            break;
        }

        return std::make_shared<CompositeElementIterator>(*this);
    }

private:
    Children children_;
};

// References:
// [Breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search)
// [Depth-first search](https://en.wikipedia.org/wiki/Depth-first_search)
// [How do I clear the std::queue efficiently?](http://stackoverflow.com/questions/709146/how-do-i-clear-the-stdqueue-efficiently)