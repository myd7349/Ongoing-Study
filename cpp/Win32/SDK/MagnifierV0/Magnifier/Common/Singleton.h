// 2015-11-24T14:43+08:00
#pragma once

#include <memory>

namespace Mag
{
namespace Utility
{

template <typename T>
class Singleton
{
public:
    static std::shared_ptr<T> GetInstancePtr()
    {
        static std::shared_ptr<T> pObj;
        if (nullptr == pObj)
        {
            pObj = std::make_shared<T>();
            ms_ObjectCreator.Dummy();
        }

        return pObj;
    }

private:
    struct ObjectCreator
    {
        ObjectCreator()
        {
            Singleton<T>::GetInstancePtr();
        }

        void Dummy() const {}
    };

    static ObjectCreator ms_ObjectCreator;

private:
    Singleton();
    ~Singleton();

    Singleton(const Singleton &);
    Singleton &operator=(const Singleton &);
};

template <typename T>
typename Singleton<T>::ObjectCreator Singleton<T>::ms_ObjectCreator;

} // namespace Utility
} // namespace Mag

// References:
// boost/container/detail/singleton.hpp
// boost/log/detail/singleton.hpp
// boost/serialization/singleton.hpp