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

https://thephd.dev/ever-closer-c23-improvements#audio-limiter

```c
#include <stddef.h>

static float clamp(float v, float lo, float hi) {
	return (v < lo) ? lo : ((hi < v) ? hi : v);
}

extern void limiter(float* data, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		data[i] = clamp(data[i], -1.0f, 1.0f);
	}
}
```

https://github.com/xqq/libaribcaption/blob/master/src/renderer/alphablend_generic.hpp#L35

```cpp
// Fast clamp to 255 algorithm
ALWAYS_INLINE uint8_t Clamp255(uint32_t x) {
    x |= -(x > 255);
    return static_cast<uint8_t>(x);
}
```
