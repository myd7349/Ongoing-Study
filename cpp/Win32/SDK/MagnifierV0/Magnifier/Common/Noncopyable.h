// 2015-11-25T13:21+08:00
#pragma once

namespace Mag
{
namespace Utility
{

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}

private:
    Noncopyable(const Noncopyable &);
    Noncopyable &operator=(const Noncopyable &);
};

} // namespace Utility
} // namespace Mag

// References:
// boost/core/noncopyable.hpp