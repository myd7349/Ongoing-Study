- TLS

  - [C++ : Handle thread-local object destruction](https://stackoverflow.com/questions/52844947/c-handle-thread-local-object-destruction)
  
  - [Can you use thread local variables inside a class or structure](https://stackoverflow.com/questions/10999131/can-you-use-thread-local-variables-inside-a-class-or-structure)
  
  - [Thread Local Storage (TLS)](https://docs.microsoft.com/en-us/cpp/parallel/thread-local-storage-tls?view=msvc-160)
  
  - [MSVC Compiler Error C2483](https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-1/compiler-error-c2483?view=msvc-160)
  
    So, in VS2010, the following will cause a compiler error C2483:
  
    ```c++
    class Background
    {
    public:
        void SetBkColor(...);
        void SetPen(...);
    
    private:
        static __declspec(thread) std::unique_ptr<Bitmap> canvas_;
    };
    ```
  
  - [C++11 thread_local destructor behaviour](https://stackoverflow.com/questions/51954025/c11-thread-local-destructor-behaviour)
  
  
