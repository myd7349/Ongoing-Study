// 2017-11-20T12:43+08:00
#include <cstdio>

// opencv2/core/types_c.h
typedef struct CvMat
{
#ifdef __cplusplus
    union
    {
        int rows;
        int height;
    };

    union
    {
        int cols;
        int width;
    };
#else
    int rows;
    int cols;
#endif
} CvMat;


int main()
{
    CvMat mat;

    mat.width = 1024;
    mat.height = 768;

    std::printf("Width: %d, Height: %d\n", mat.width, mat.height);
    std::printf("Cols: %d, Rows: %d\n", mat.cols, mat.rows);

    return 0;
}
