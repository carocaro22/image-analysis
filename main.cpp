#include <opencv2/opencv.hpp>
#include "indexing.h"

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    cv::Vec3b bg = cv::Vec3b(0, 0, 0);

    std::list<std::vector<std::pair<int, int>>> objectList = indexAndColor(img, bg); 

    cv::imshow("Index", img);
    cv::waitKey(0);
     
    return 0;
}