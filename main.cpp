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
        sum_f1 = sum_f1 + feature1(img, objects.front()); 
        sum_f2 = sum_f2 + feature2(objects.front());
        objects.pop_front();
    }

    double avg_f1 = sum_f1 / size;
    double avg_f2 = sum_f2 / size;

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
        std::cout << element.first << " f1 average: " << element.second.first << std::endl;
        std::cout << element.first << " f2 average: " << element.second.second << std::endl;
        e.pop_back();
    }
    double min = std::min(distances[0], std::min(distances[1], distances[2]));
    if (min == distances[0]) {
            return "rectangle";
    }
    else if (min == distances[1]) {
            return "star";
    }
    else if (min == distances[2]) {
            return "square";
    } else {
        return "could not identify object";
    }
}

cv::Mat plt_ethalons(std::vector<std::pair<cv::Scalar, std::pair<double, double>>> data) {
    cv::Mat image(300, 300, CV_8UC3);
    image.setTo(cv::Scalar(255, 255, 255));

    int width = 300;
    int height = 300;
    double min_value = 0.0;
    double max_value = 1.0;
    double x_scale = static_cast<double>(width) / (max_value - min_value);
    double y_scale = static_cast<double>(height) / (max_value - min_value);


    for (int i = 0; i < data.size(); i++) {
    int x = x_scale * (data[i].second.first - min_value);
    int y = height - y_scale * (data[i].second.second - min_value);  // Invert y for bottom-left origin

    cv::circle(image, cv::Point(x, y), 5, data[i].first, -1);
    }

    return image;
}


int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    cv::Vec3b bg = cv::Vec3b(0, 0, 0);
    std::list<std::vector<std::pair<int, int>>> objectList = indexAndColor(img, bg);
    
    std::list<std::pair<std::string, std::pair<double, double>>> e = ethalons(img, objectList);

    double f1;
    double f2;

    std::cin >> f1;
    std::cin >> f2; 

    std::cout << classify(f1, f2, e) << std::endl;

    std::vector<std::pair<cv::Scalar, std::pair<double, double>>> data;

    int length = e.size();

    for (int i; i < length; i++) {
        data.push_back(std::make_pair(cv::Scalar(255, 0, 0),e.back().second));
        e.pop_back();
    }
    
    data.push_back(std::make_pair(cv::Scalar(0, 255, 0), std::make_pair(f1, f2)));

    cv::Mat plot = plt_ethalons(data);

    cv::imshow("Graph", plot);
    cv::imshow("Index", img);
    cv::waitKey(0);
     
    return 0;
}