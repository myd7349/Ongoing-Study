#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>


int main()
{
    std::deque<int> deq;

    auto print_deq = [](std::ostream &os, const std::deque<int> &deq) {
        os << '[';
        
        std::copy(deq.cbegin(), deq.cend() - 1, std::ostream_iterator<int>(os, ", "));
        if (!deq.empty())
            os << deq.back();

        os << "]\n";
    };

    auto cout_deq = std::bind(print_deq, std::ref(std::cout), std::placeholders::_1);

    int nums[] = { 1, 2, 3, 4, 5 };

    // inserter
    std::copy(std::cbegin(nums), std::cend(nums), std::inserter(deq, deq.begin()));
    cout_deq(deq);

    deq.clear();

    // front_inserter
    std::copy(std::cbegin(nums), std::cend(nums), std::front_inserter(deq));
    cout_deq(deq);

    std::cin.get();

    return 0;
}

// References:
// C++ Primer, 5th Edition, 10.4.1 Insert Iterators
// cppreference
