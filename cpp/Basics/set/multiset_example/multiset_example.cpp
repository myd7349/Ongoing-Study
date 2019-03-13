#include <iostream>
#include <set>
#include <string>


struct Item
{
    std::string type;
    int quantity;
};


inline bool operator<(const Item &lhs, const Item &rhs)
{
    return lhs.type < rhs.type;
}


int main()
{
    std::multiset<Item> items;

    items.insert({ "A", 1 });
    items.insert({ "B", 2 });

    items.insert({ "A", 11 });
    items.insert({ "B", 22 });

    items.insert({ "A", 111 });
    items.insert({ "B", 222 });

    for (auto it = items.cbegin();
        it != items.cend();
        it = items.upper_bound(*it))
    {
        auto iit = it;

        for (std::multiset<Item>::size_type i = 0; i < items.count(*it); ++i)
        {
            std::cout << iit->type << ": " << iit->quantity << '\n';
            ++iit;
        }
    }

    return 0;
}


// References:
// C++ Primer, 5th Edition, 15.8.1
