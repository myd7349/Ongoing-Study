[good idiom for empty containers with std::all_of( ) and std:none_of( )?](https://stackoverflow.com/questions/15555218/good-idiom-for-empty-containers-with-stdall-of-and-stdnone-of)
> Both std::all_of( ) and std:none_of( ) return true for empty containers.

[Add value to elements of a vector](https://stackoverflow.com/questions/27847128/using-for-loop-to-add-numbers-to-a-vector)
```cpp
std::vector<int> v { 1, 2, 3, 4, 5 };
std::for_each(v.begin(), v.end(), [](int &x) { x += 1000; });
```
