// 2014-04-01T11:26+08:00
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

void usage()
{
    std::cout << "Usage: \n\tResize> imgconv.exe factor infile outfile" << std::endl;
    std::cout << "\tTranspose horizontally> imgconv.exe infile outfile" << std::endl;
}

int resizeImage(int argc, char *argv[])
{
    double factor = std::strtod(argv[1], NULL);
    if (factor < 1e-7) {
        factor = 1.0;
    }

    std::string srcImg = argv[2];
    std::string dstImg = argv[3];

    cv::Mat srcImgMat = cv::imread(srcImg, -1);
    if (srcImgMat.empty()) {
        std::cerr << "Open image \"" << srcImg << "\" failed.\n";
        return 1;
    }

#ifndef NDEBUG
    cv::imshow("Source image", srcImgMat);
    cv::waitKey();
#endif // NDEBUG

    cv::Mat dstImgMat;
    cv::resize(srcImgMat, dstImgMat, cv::Size(), factor, factor);

    cv::imwrite(dstImg, dstImgMat);

    return 0;
}

int transImage(int argc, char *argv[])
{
    std::string srcImg = argv[1];
    std::string dstImg = argv[2];

    // We need the alpha channel
    cv::Mat srcImgMat = cv::imread(srcImg, -1);
    if (srcImgMat.empty()) {
        std::cerr << "Open image \"" << srcImg << "\" failed.\n";
        return 1;
    }

    if (srcImgMat.depth() != CV_8U) {
        std::cerr << "Unsupported image type.\n";
        return 2;
    }

#ifndef NDEBUG
    cv::imshow("Source image", srcImgMat);
    cv::waitKey();
#endif // NDEBUG

    int rows = srcImgMat.rows;
    int cols = srcImgMat.cols;
    int channels = srcImgMat.channels();

    switch (channels) {
    case 1:
        for (int i = 0; i < rows; ++i) {
            unsigned char *beg = srcImgMat.ptr(i);
            unsigned char *end = beg + cols * channels;
            while (beg != end) {
                std::iter_swap(beg++, --end);
            }
        }
        break;
    case 3:
        for (int i = 0; i < rows; ++i) {
            unsigned char *beg = srcImgMat.ptr(i);
            unsigned char *end = beg + cols * channels;
            while (beg != end) {
                end -= channels;
                std::iter_swap(beg++, end);
                std::iter_swap(beg++, end + 1);
                std::iter_swap(beg++, end + 2);
            }
        }
        break;
    case 4:
        for (int i = 0; i < rows; ++i) {
            unsigned char *beg = srcImgMat.ptr(i);
            unsigned char *end = beg + cols * channels;
            while (beg != end) {
                end -= channels;
                std::iter_swap(beg++, end);
                std::iter_swap(beg++, end + 1);
                std::iter_swap(beg++, end + 2);
                std::iter_swap(beg++, end + 3);
            }
        }
        break;
    default: break;
    }

    cv::imwrite(dstImg, srcImgMat);

    return 0;
}

int main(int argc, char *argv[])
{
    switch (argc) {
    case 3:
        return transImage(argc, argv);
    case 4:
        return resizeImage(argc, argv);
    default:
        usage();
        return 0;
    }
}
