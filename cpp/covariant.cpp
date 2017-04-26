// 2017-04-26T15:27+08:00
#include <iostream>
#include <memory>

template <typename T>
struct Iterator
{
    virtual void Describe() = 0;
};

template <typename T>
struct NullIterator : Iterator<T>
{
    virtual void Describe()
    {
        std::cout << "NullIterator<" << typeid(T).name() << ">" << std::endl;
    }
};

template <typename T>
struct CompositionIterator : Iterator<T>
{
    virtual void Describe()
    {
        std::cout << "CompositionIterator<" << typeid(T).name() << ">" << std::endl;
    }
};

struct Component;

struct Iterable
{
    virtual Iterator<Component> *CreateIterator() = 0;
};

struct Component : public Iterable
{
    virtual Iterator<Component> *CreateIterator()
    {
        return new NullIterator<Component>();
    }
};

struct CompositeComponent : public Iterable
{
    virtual CompositionIterator<Component> *CreateIterator()
    {
        return new CompositionIterator<Component>();
    }
};

struct Layout : public CompositeComponent
{
};

#if 0
struct NestedLayout : public CompositeComponent
{
    // error:
    virtual CompositionIterator<Layout> *CreateIterator()
    {
        return new CompositionIterator<Layout>();
    }
};
#endif

int main()
{
    {
        std::unique_ptr<Iterator<Component>>(
            std::unique_ptr<Component>(new Component())->CreateIterator())
            ->Describe();
        
#if 0
        // error:
        std::unique_ptr<Component>(new Layout());
#endif

        std::unique_ptr<Iterator<Component>>(
            std::unique_ptr<Layout>(new Layout())->CreateIterator())
            ->Describe();
    }

    std::cin.get();

    return 0;
}