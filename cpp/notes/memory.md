[Difference between std::lock_guard and std::unique_lock](http://jakascorner.com/blog/2016/02/lock_guard-and-unique_lock.html)

https://github.com/microsoft/vcpkg/pull/7443

https://github.com/Liam0205/liam0205.github.io/tree/master/2020/04/21/managing-FILE-pointer-by-std-unique-ptr

[Smart Pointers Make Bad APIs](https://vector-of-bool.github.io/2018/12/02/smart-pointer-apis.html)

[SEI CERT C++ Coding Standard](https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=88046682)

[EXP57-CPP. Do not cast or delete pointers to incomplete classes](https://wiki.sei.cmu.edu/confluence/display/cplusplus/EXP57-CPP.+Do+not+cast+or+delete+pointers+to+incomplete+classes)

https://github.com/assimp/assimp/blob/199aa5dd663402d4d3461876c9846c45b616699d/include/assimp/metadata.h#L250

> delete static_cast<int32_t *>(data);

[C++ delete static_cast (pointer) behavior](https://stackoverflow.com/questions/2709283/c-delete-static-castvoid-pointer-behavior)

[best method to delete a type cast pointer](https://stackoverflow.com/questions/44162883/best-method-to-delete-a-type-cast-pointer)

[How to find memory leak in a C++ code/project?](https://stackoverflow.com/questions/6261201/how-to-find-memory-leak-in-a-c-code-project)

[When is std::weak_ptr useful?](https://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful)

[std::shared_ptr thread safety](https://stackoverflow.com/questions/14482830/stdshared-ptr-thread-safety)

unique_ptr vs HANDLE

- [用 unique_ptr 管理 Windows HANDLE](https://kingsamchen.github.io/2021/06/14/wrap-win32-handle-into-unique-ptr/) - [unique-ptr-as-scoped-handle](https://github.com/kingsamchen/Eureka/tree/master/unique-ptr-as-scoped-handle)
- https://chromium.googlesource.com/chromium/src/+/refs/heads/main/base/win/scoped_handle.h

