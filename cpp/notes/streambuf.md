https://en.cppreference.com/w/cpp/io/basic_streambuf

[Standard no-op output stream](https://stackoverflow.com/questions/11826554/standard-no-op-output-stream)

```cpp
class NullBuffer : public std::streambuf
{
public:
  int overflow(int c) { return c; }
};

NullBuffer null_buffer;
std::ostream null_stream(&null_buffer);
null_stream << "Nothing will be printed";
```

https://github.com/jwakely/pstreams

[UTF-8 output on Windows console](https://stackoverflow.com/questions/1660492/utf-8-output-on-windows-console)
