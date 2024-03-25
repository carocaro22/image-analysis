#include <opencv2/opencv.hpp>
#include "indexing.h"
#include "features.h"
#include <stdio.h>

std::vector<std::vector<std::pair<int, int>>> select3RandomObjects(std::vector<std::vector<std::pair<int, int>>> objectsvector) {
    std::vector<std::vector<std::pair<int, int>>> randomObjects;
    for (int i = 0; i < 3; i++) {
        int index = rand() % 12;
        randomObjects.push_back(objectsvector[index]);
    } 
    return randomObjects;
}

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    cv::Vec3b bg = cv::Vec3b(0, 0, 0);
    // Object.point[index].x; Object.point[index].y
    std::list<std::vector<std::pair<int, int>>> objectList = indexAndColor(img, bg);

    std::vector<std::vector<std::pair<int, int>>> objectVector;

    for (auto object: objectList) {
        objectVector.push_back(object);
    }

    std::cout << select3RandomObjects(objectVector).size() << std::endl;

    cv::waitKey(0);
    return 0;
}