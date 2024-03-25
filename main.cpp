#include <opencv2/opencv.hpp>
#include "indexing.h"
#include "features.h"
#include <stdio.h>

// first is average of feature 1
// second is average of feature 2
// lower_bound included but upper_bound not included
std::pair<double, double> ethalon(cv::Mat img, std::list<std::vector<std::pair<int,int>>> & objects, int lower_bound, int upper_bound) {
    double sum_f1 = 0;
    double sum_f2 = 0;
    int size = upper_bound - lower_bound;

    for (int i = lower_bound; i < upper_bound; i++) {
        double f1 = feature1(img, objects.front()); 
        // std::cout << "result f1 = " << f1 << std::endl;
        sum_f1 = sum_f1 + f1;
        
        sum_f2 = sum_f2 + feature2(objects.front());
        objects.pop_front();
    }

    double avg_f1 = sum_f1 / size;
    double avg_f2 = sum_f2 / size;

    // std::cout << "avg_f1: " << avg_f1 << std::endl;
    // std::cout << "avg_f2_min: " << avg_f2_min << std::endl;
    // std::cout << "avg_f2_max: " << avg_f2_max << std::endl;

    std::pair<double, double> features; 
    features.first = avg_f1;
    features.second = avg_f2;
    return features;
}

std::list<std::pair<std::string, std::pair<double, double>>> ethalons(cv::Mat & img, std::list<std::vector<std::pair<int, int>>> & objects) {
    std::pair<double, double> square = ethalon(img, objects, 0, 4);
    std::pair<double, double> stars = ethalon(img, objects, 4, 8);
    std::pair<double, double> rectangles = ethalon(img, objects, 8, 12);
    std::list<std::pair<std::string, std::pair<double,double>>> list;
    list.push_back(std::make_pair("square" , square));
    list.push_back(std::make_pair("star", stars));
    list.push_back(std::make_pair("rectangle", rectangles));
    return list;
}

std::string classify(double f1, double f2, std::list<std::pair<std::string, std::pair<double, double>>> e ) {
    int size = e.size();
    std::vector<double> distances;

    for (int i = 0; i < size; i++) {
        std::pair<std::string, std::pair<double, double>> element = e.back();
        double distance = std::sqrt(pow(f1 - element.second.first, 2) + pow(f2 - element.second.second, 2)); 
        distances.push_back(distance); 
        std::cout << element.first << " f2_min average: " << element.second.first << std::endl;
        std::cout << element.first << " f1 average: " << element.second.second << std::endl;
        e.pop_back();
    }
    double min = std::min(distances[0], std::min(distances[1], distances[2]));
    
    if (min == distances[0]) {
            return "rectangle";
    }
    if (min == distances[1]) {
            return "star";
    }
    if (min == distances[2]) {
            return "square";
    }
    // should never happen
    return "could not identify object";
}

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    cv::Vec3b bg = cv::Vec3b(0, 0, 0);
    std::list<std::vector<std::pair<int, int>>> objectList = indexAndColor(img, bg);
    
    std::list<std::pair<std::string, std::pair<double, double>>> e = ethalons(img, objectList);
    std::cout << classify(0.93, 0.77, e) << std::endl;

    cv::imshow("Index", img);
    cv::waitKey(0);
     
    return 0;
}