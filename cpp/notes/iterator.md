[Avoid inheritance from std::iterator](https://github.com/Tencent/rapidjson/pull/1137)

[Testing whether an iterator points to the last item?](https://stackoverflow.com/questions/3516196/testing-whether-an-iterator-points-to-the-last-item)

```cpp
if (it == std::prev(lst.end())) {
}
```

```cpp
#include <iterator>

// Note: Use std::prev, std::next instead.
template <typename InputIterator, typename Distance>
InputIterator Advance(InputIterator it, Distance offset)
{
    InputIterator targetIterator = it;
    std::advance(targetIterator, offset);
    return targetIterator;
}
```
