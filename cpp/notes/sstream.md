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
```
std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

if(VertexShaderStream.is_open()) {
    std::stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    VertexShaderCode = sstr.str();
    VertexShaderStream.close();
}
```
