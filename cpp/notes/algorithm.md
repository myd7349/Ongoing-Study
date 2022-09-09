[good idiom for empty containers with std::all_of( ) and std:none_of( )?](https://stackoverflow.com/questions/15555218/good-idiom-for-empty-containers-with-stdall-of-and-stdnone-of)
> Both std::all_of( ) and std:none_of( ) return true for empty containers.

[Add value to elements of a vector](https://stackoverflow.com/questions/27847128/using-for-loop-to-add-numbers-to-a-vector)
```cpp
std::vector<int> v { 1, 2, 3, 4, 5 };
std::for_each(v.begin(), v.end(), [](int &x) { x += 1000; });
```

[Problem calling std::max](https://stackoverflow.com/questions/2789481/problem-calling-stdmax/2789509#2789509)

[#define NOMINMAX using std::min/max](https://stackoverflow.com/questions/13416418/define-nominmax-using-stdmin-max)

[How to find minimum element in a given range of indices for a vector?](https://stackoverflow.com/questions/54470808/how-to-find-minimum-element-in-a-given-range-of-indices-for-a-vector)

[How to find minimum distance using lambda](https://stackoverflow.com/questions/61595990/how-to-find-minimum-distance-using-lambda)

[adjacent_find](https://zed0.co.uk/clang-format-configurator/)

```cpp
template <typename T, int size>
bool is_sorted(T (&array)[size]) {
  return std::adjacent_find(array, array + size, std::greater<T>()) ==
         array + size;
}
```
