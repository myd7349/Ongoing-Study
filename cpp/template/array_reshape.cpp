// 2018-07-14T18:18+08:00
#include <algorithm>
#include <iostream>


template <int ROWS, int COLS>
void PrintArr(int (&arr)[ROWS][COLS])
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
            std::cout << arr[i][j] << '\t';

        std::cout << '\n';
    }
}


template <int SIZE, int ROWS>
void Reshape(int (&raw)[SIZE], int (&arr)[ROWS][SIZE / ROWS])
{
    const int COLS = SIZE / ROWS;

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
            arr[i][j] = raw[i * COLS + j];
    }
}


int main()
{
    int raw[12];
    std::iota(std::begin(raw), std::end(raw), 0);

    int arr[3][4];
    Reshape(raw, arr);
    PrintArr(arr);

    return 0;
}

/*
VS2010/VS2017:
error C2039: 'iota' : is not a member of 'std'
error C3861: 'iota': identifier not found
error C2783: 'void Reshape(int (&)[SIZE],int (&)[ROWS][SIZE/ROWS])' : could not deduce template argument for 'ROWS'

Code::Blocks 17.12:
OK
*/


// References:
// https://stackoverflow.com/questions/1745942/c-template-parameter-in-array-dimension


