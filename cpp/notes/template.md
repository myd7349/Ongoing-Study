[pointer non-type template parameter](https://stackoverflow.com/questions/29001446/pointer-non-type-template-parameter)

[Default template parameter in constructor](https://stackoverflow.com/questions/831952/default-template-parameter-in-constructor)

> Note that default template parameters are not allowed for function templates. Why not create a class template?
> 
> ```cpp
> template <class T=int>
> class mama{
>     public:
>     mama<T>(T i=0){}
> };
> 
> int main(){
>     mama<> x; // no argument based template parameter deduction possible
> }
> ```

[Can a non-type template parameter be of type "void*"?](https://stackoverflow.com/questions/56003162/can-a-non-type-template-parameter-be-of-type-void)

> Template parameters of type `void*` are valid since C++20.
> They are invalid prior to C++20.
