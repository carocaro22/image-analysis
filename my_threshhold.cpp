#include "my_threshhold.h"

void myThreshhold(cv::Mat img, cv::Vec3b threshhold, cv::Vec3b color) {
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            if (
              img.at<cv::Vec3b>(i,j)[0] > threshhold[0]
            && img.at<cv::Vec3b>(i,j)[1] > threshhold[1]
            && img.at<cv::Vec3b>(i,j)[2] > threshhold[2] ) {
                img.at<cv::Vec3b>(i,j) = color;
            }
        }
    }
}

