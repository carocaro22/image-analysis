#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void myThreshhold(Mat img, Vec3b threshhold, Vec3b color) {

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            if (
              img.at<Vec3b>(i,j)[0] > threshhold[0]
            && img.at<Vec3b>(i,j)[1] > threshhold[1]
            && img.at<Vec3b>(i,j)[2] > threshhold[2] ) {
                img.at<Vec3b>(i,j) = color;
            }
        }
    }
}

int main(int argc, char** argv)
{
    Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    Vec3b threshhold = Vec3b(127, 127, 127);
    Vec3b red = Vec3b(0, 0, 255);

    myThreshhold(img, threshhold, red);

    imshow("Threshhold", img);
    waitKey(0);
     
    return 0;
}