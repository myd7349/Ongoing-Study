https://github.com/lemire/simdjson/pull/344/files
```cpp
size_t sum_line_lengths(char * data, size_t length) {
  std::stringstream is;
  is.rdbuf()->pubsetbuf(data, length);
  std::string line;
  size_t sumofalllinelengths{0};
  while(getline(is, line)) {
    sumofalllinelengths += line.size();
  }
  return sumofalllinelengths;
}
```

https://github.com/opengl-tutorials/ogl/blob/316cccc5f76f47f09c16089d98be284b689e057d/common/shader.cpp#L25-L30
```cpp
std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

if(VertexShaderStream.is_open()) {
    std::stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    VertexShaderCode = sstr.str();
    VertexShaderStream.close();
}
```

[How to use stringstream to separate comma separated strings](https://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings)
```cpp
#include <iostream>
#include <sstream>

std::string input = "abc,def,ghi";
std::istringstream ss(input);
std::string token;

while(std::getline(ss, token, ',')) {
    std::cout << token << '\n';
}
```
