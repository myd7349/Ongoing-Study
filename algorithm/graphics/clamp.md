https://en.wikipedia.org/wiki/Clamping_(graphics)

https://en.cppreference.com/w/cpp/algorithm/clamp

https://github.com/ArthurSonzogni/FTXUI/pull/306

```cpp
template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi)
{
    return v < lo ? lo : hi < v ? hi : v;
}
```

https://github.com/reneschulte/WriteableBitmapEx/blob/WBX_NuGet_1_6_2/Source/WriteableBitmapEx/WriteableBitmapTransformationExtensions.cs#L100-L105

