[How to retrieve all keys (or values) from a std::map and put them into a vector?](https://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap-and-put-them-into-a-vector)

[C++中P.J. Plauger STL和SGI STL中map的区别](https://blog.csdn.net/donhao/article/details/6636098)

P.J. Plauger STL:
```cpp
for(ITER iter = mapTest.begin(); iter != mapTest.end();) 
{ 
    iter = mapTest.erase(iter); 
}
```

SGI STL:
```cpp
for(ITER iter = mapTest.begin(); iter != mapTest.end();) 
{ 
    mapTest.erase(iter++); 
}
```

https://github.com/martinus/map_benchmark

https://github.com/endless-sky/endless-sky/blob/master/source/Dictionary.h
