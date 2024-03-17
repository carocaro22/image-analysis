#include <opencv2/opencv.hpp>
#include "indexing.h"
#include "features.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    cv::Vec3b bg = cv::Vec3b(0, 0, 0);

    std::list<std::vector<std::pair<int, int>>> objectList = indexAndColor(img, bg);
    int listSize = objectList.size();
    std::cout << listSize << std::endl; 
    
    for (int i = 0; i < listSize; i++) {
        std::vector<std::pair<int,int>> obj = objectList.front();
        objectList.pop_front();
        int obj_area = area(obj); 
        int obj_circumference = circumference(img, obj);
        std::cout << "index: " << i << std::endl;
        std::cout << "area: " << obj_area << std::endl;
        std::cout << "circumference: " << obj_circumference << std::endl;
        std::cout << "" << std::endl;
    }

    cv::imshow("Index", img);
    cv::waitKey(0);
     
    return 0;
}