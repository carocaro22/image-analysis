#include <opencv2/opencv.hpp>
#include "indexing.h"
#include <stdio.h>
#include <utility>
#include <vector>

float m(std::vector<std::pair<int,int>>obj, float p, float q) {
    float sum = 0;
    for (int i = 0; i < obj.size(); i++) {
        float x = obj.at(i).first; 
        float y = obj.at(i).second;
        float x_p = std::pow(x, p);
        float y_q = std::pow(y, q);
        sum = sum + (x_p*y_q);
    }
    return sum;
}

float area(std::vector<std::pair<int,int>> obj) {
    return m(obj, 0, 0); 
}

std::pair<float,float> center_of_mass(std::vector<std::pair<int,int>> obj) {
    float x_t = m(obj, 1, 0) / area(obj);
    float y_t = m(obj, 0, 1) / area(obj);
    return std::pair<float,float>(x_t, y_t);
}

int circumference(cv::Mat img, std::vector<std::pair<int, int>> obj) {
    cv::Vec3b color = img.at<cv::Vec3b>(obj.front().first, obj.front().second);
    int circumference = 0;

    for (int i = 0; i < obj.size(); i++) {
        int x = obj.at(i).first;
        int y = obj.at(i).second;
        if (img.at<cv::Vec3b>(x + 1, y) != color
        || img.at<cv::Vec3b>(x - 1, y) != color
        || img.at<cv::Vec3b>(x, y + 1) != color
        || img.at<cv::Vec3b>(x, y - 1) != color
        ) {
            circumference++; 
        }
    }

    return circumference;
}

float mu(std::vector<std::pair<int,int>> obj, float p, float q) {
    float x_t = center_of_mass(obj).first;
    float y_t = center_of_mass(obj).second;
    float sum  = 0;
    for (int i = 0; i < obj.size(); i++) {
        int x = obj.at(i).first;
        int y = obj.at(i).second;
        float a = pow((x - x_t), p);
        float b = pow((y - y_t), q);
        float result = a*b;
        sum = sum + result;
    }
    return sum;
}

float feature1(cv::Mat img, std::vector<std::pair<int,int>> obj) {
    float result = pow(circumference(img, obj), 2) / (100*area(obj));
    return result;
}

std::pair<float, float> feature2(std::vector<std::pair<int, int>> o) {
    float mu_a = 0.5*(mu(o,2,0) + mu(o,0,2));
    float mu_b = 0.5*(sqrt(4*pow(mu(o,1,1), 2) + pow(mu(o,2,0)-mu(o,0,2), 2)));
    return std::pair<float, float>(mu_a + mu_b, mu_a - mu_b);
}

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    cv::Vec3b bg = cv::Vec3b(0, 0, 0);

    std::list<std::vector<std::pair<int, int>>> objectList = indexAndColor(img, bg);
    std::cout << objectList.size() << std::endl; 
    
    for (int i = 0; i < objectList.size(); i++) {
        std::vector<std::pair<int,int>> obj = objectList.front();
        objectList.pop_front();
        int obj_area = area(obj); 
        int obj_circumference = circumference(img, obj);
        //std::cout << "index: " << i << std::endl;
        //std::cout << "area: " << obj_area << std::endl;
        //std::cout << "circumference: " << obj_circumference << std::endl;
        //std::cout << "" << std::endl;
    }

    cv::imshow("Index", img);
    cv::waitKey(0);
     
    return 0;
}