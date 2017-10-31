// 2015-03-22T17:44+08:00
#include <functional>
#include <iterator>
#include <string>

#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"


void InsertionSortTest()
{
    std::cout << __func__ << std::endl;

    std::vector<int> ivec {5, 2, 4, 6, 1, 3};
    InsertionSort(ivec.begin(), ivec.end(), std::less<int>());

    int best_worst[] {0, 1, 2, 3, 4, 5};
    InsertionSort(std::begin(best_worst), std::end(best_worst), std::less<int>());
    InsertionSort(std::begin(best_worst), std::end(best_worst), std::greater<int>());
}

void MergeSortTest()
{
    std::cout << __func__ << std::endl;

    std::vector<int> ivec {5, 2, 4, 6, 3};
    MergeSort(ivec.begin(), ivec.end(), std::less<int>());

    int arr[] {2, 3, 8, 1, 4, 5, 7, 6};
    MergeSort(std::begin(arr), std::end(arr), std::less<int>());
    MergeSort(std::begin(arr), std::end(arr), std::greater<int>());
}

void QuickSortTest()
{
    std::cout << __func__ << std::endl;

    int arr[] {2, 3, 8, 1, 4, 5, 7, 6};
    QuickSort(std::begin(arr), std::end(arr));
}

int main()
{
    //InsertionSortTest();
    MergeSortTest();
#if 0
    auto fib = [&](int i) {
        if (0 == i || 1 == i) {
            return 1;
        }
        return fib(i - 1) * i;
    };

    std::cout << fib(1) << std::endl;
    std::cout << fib(2) << std::endl;
    std::cout << fib(3) << std::endl;
#endif

    QuickSortTest();

    return 0;
}
