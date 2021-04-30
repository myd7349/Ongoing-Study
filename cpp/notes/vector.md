[how do you insert the value in a sorted vector?](https://stackoverflow.com/questions/15843525/how-do-you-insert-the-value-in-a-sorted-vector)
```cpp
template< typename T >
typename std::vector<T>::iterator 
   insert_sorted( std::vector<T> & vec, T const& item )
{
    return vec.insert
        ( 
            std::upper_bound( vec.begin(), vec.end(), item ),
            item 
        );
}


template< typename T, typename Pred >
typename std::vector<T>::iterator
    insert_sorted( std::vector<T> & vec, T const& item, Pred pred )
{
    return vec.insert
        ( 
           std::upper_bound( vec.begin(), vec.end(), item, pred ),
           item 
        );
}


const char *unsorted[] = { "赵", "钱", "孙", "李" };

std::vector<std::string> names;

for (int i = 0; i < 4; ++i)
{
    names.insert(
        std::upper_bound(names.cbegin(), names.cend(), unsorted[i],
            [](const std::string &new_name, const std::string &existed)
            {
                return strcoll(new_name.c_str(), existed.c_str()) < 0;
            }),
        unsorted[i]);
}

```

https://github.com/p-ranav/small_vector

