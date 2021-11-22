#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <tinyfiledialogs/tinyfiledialogs.h>

#include "../../common.h"


namespace
{
    bool isInteractiveMode = false;

    cv::String GetInputFileName(int argc, char * const argv[])
    {
        if (argc >= 2)
            return argv[1];

        const char *patterns[] =
        {
            "*.bmp",
            "*.jpg",
            "*.jpeg",
            "*.png",
        };

        return tinyfd_openFileDialog(
            "Select the original signature:",
            NULL,
            ARRAYSIZE(patterns),
            patterns,
            "Image Files (*.bmp;*.jpg;*.jpeg;*.png)",
            0
        );
    }

    cv::String GetOutputFileName(int argc, char * const argv[])
    {
        if (argc >= 3)
            return argv[2];

        return tinyfd_saveFileDialog(
            "Where to save the processed signature?",
            NULL,
            0,
            NULL,
            NULL
        );
    }

    void ShowImage(cv::String title, cv::InputArray image)
    {
        if (isInteractiveMode)
            cv::imshow(title, image);
    }

    void ShowError(cv::String title, cv::String text)
    {
        if (isInteractiveMode)
        {
            tinyfd_messageBox(
                title.c_str(),
                text.c_str(),
                "ok",
                "error",
                0
            );
        }
        else
        {
            std::cerr << title << ": " << text << '\n';
        }
    }

    void WaitKey()
    {
        cv::waitKey();
    }
}


int main(int argc, char *argv[])
{
    isInteractiveMode = argc < 3;

    cv::String inputFile = GetInputFileName(argc, argv);
    if (inputFile.empty())
    {
        ShowError("Error", "Operation cancelled!");
        return EXIT_FAILURE;
    }

    auto rawSignature = cv::imread(inputFile);
    if (rawSignature.empty())
    {
        ShowError("Failed to load original signature", inputFile);
        return EXIT_FAILURE;
    }

    if (isInteractiveMode)
        std::atexit(WaitKey);

    ShowImage("Source signature", rawSignature);

    cv::Mat intermediateImage;
    cv::cvtColor(rawSignature, intermediateImage, cv::COLOR_BGR2GRAY);
    ShowImage("Gray signature", intermediateImage);

    cv::threshold(intermediateImage, intermediateImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    ShowImage("Binary signature", intermediateImage);

    std::vector<std::vector<cv::Point>> contours;

#if 0
    cv::findContours(intermediateImage, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    if (!contours.empty())
        contours.pop_back();
#else
    cv::bitwise_not(intermediateImage, intermediateImage);
    ShowImage("Invert black and white", intermediateImage);
    cv::findContours(intermediateImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
#endif

    cv::Rect boundingBox;
    for (decltype(contours)::size_type i = 0; i < contours.size(); ++i)
    {
        boundingBox |= cv::boundingRect(contours[i]);
        std::cout << boundingBox << std::endl;
    }

#ifndef NDEBUG
    rawSignature.copyTo(intermediateImage);
    cv::rectangle(intermediateImage, boundingBox, cv::Scalar(255, 0, 255, 128));
    ShowImage("Bounding box", intermediateImage);
#endif

    if (!boundingBox.empty())
    {
        cv::Mat destSignature = rawSignature(boundingBox);
        ShowImage("Final", destSignature);

        cv::String outputFile = GetOutputFileName(argc, argv);
        if (outputFile.empty())
        {
            ShowError("Error", "Operation cancelled!");
            return EXIT_FAILURE;
        }

        if (!cv::imwrite(outputFile, destSignature))
        {
            ShowError("Failed to write to the target file", outputFile);
            return EXIT_FAILURE;
        }
    }

    return 0;
}


// References:
// https://www.quora.com/How-can-I-detect-an-object-from-static-image-and-crop-it-from-the-image-using-openCV
// https://stackoverflow.com/questions/13538748/crop-black-edges-with-opencv
// https://stackoverflow.com/questions/17141535/how-to-use-the-otsu-threshold-in-opencv
// https://docs.opencv.org/3.1.0/df/d0d/tutorial_find_contours.html
// https://stackoverflow.com/questions/8449378/finding-contours-in-opencv
// https://homepages.inf.ed.ac.uk/rbf/HIPR2/dilate.htm
// https://stackoverflow.com/questions/44383209/how-to-detect-edge-and-crop-an-image-in-python
// https://www.learnopencv.com/filling-holes-in-an-image-using-opencv-python-c/
// https://stackoverflow.com/questions/1716274/fill-the-holes-in-opencv
// https://www.learnopencv.com/filling-holes-in-an-image-using-opencv-python-c/
// https://www.geometrictools.com/Source/ComputationalGeometry.html
// [graphicsmagick how to remove transparent area and shrink the canvas size of a 32-bit image](https://stackoverflow.com/questions/19827613/graphicsmagick-how-to-remove-transparent-area-and-shrink-the-canvas-size-of-a-32)
// > gm convert input.png -trim +repage output.png
