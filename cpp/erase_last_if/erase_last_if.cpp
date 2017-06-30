// 2017-06-30T08:25+08:00
#include <algorithm>
#include <iostream>
#include <list>

#include "../common.h"


class Person
{
public:
    Person(int age)
        : age_(age)
    {
    }

    int GetAge() const
    {
        return age_;
    }

private:
    int age_;
};

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    return os << "Person(" << p.GetAge() << ")";
}

int main()
{
    std::list<Person> lst { 8, 42, 13, 100, 200, 80 };
    Println(lst);

    auto it = std::find_if(lst.rbegin(), lst.rend(), [](const Person &p)->bool { return p.GetAge() > 120; });
    if (it != lst.rend())
    {
        std::advance(it, 1);
        lst.erase(it.base());
        Println(lst);
    }

    return 0;
}

// References:
// [How to call erase with a reverse iterator](https://stackoverflow.com/questions/1830158/how-to-call-erase-with-a-reverse-iterator)
// [vector::erase and reverse_iterator](https://stackoverflow.com/questions/11490242/vectorerase-and-reverse-iterator)
