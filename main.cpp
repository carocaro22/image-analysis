#include <stdio.h>
#include <utility>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stack>
#include <list>

std::vector<std::pair<int, int>> indexObject(cv::Mat &img, std::pair<int, int> start, cv::Vec3b bg, cv::Vec3b color) {
    std::stack<std::pair<int, int>> stack;
    std::vector<std::pair<int, int>> pixels;
    stack.push(start);
    while (!(stack.empty())) {
        // Current coordinates
        std::pair c = stack.top();
        stack.pop();
        pixels.push_back(c); 
        img.at<cv::Vec3b>(c.first, c.second) = color;
        
        if (img.at<cv::Vec3b>(c.first + 1, c.second) != bg
        && img.at<cv::Vec3b>(c.first + 1, c.second) != color 
        ) {
            std::pair<int,int> l = std::make_pair(c.first + 1, c.second);
            stack.push(l);
        }
        if (img.at<cv::Vec3b>(c.first - 1, c.second) != bg
        && img.at<cv::Vec3b>(c.first - 1, c.second) != color 
        ) {
            std::pair<int,int> o = std::make_pair(c.first - 1, c.second);
            stack.push(o);
        }
        if (img.at<cv::Vec3b>(c.first, c.second + 1) != bg
        && img.at<cv::Vec3b>(c.first, c.second + 1) != color 
        ) {
            std::pair<int,int> s = std::make_pair(c.first, c.second + 1);
            stack.push(s);
        }
        if (img.at<cv::Vec3b>(c.first, c.second - 1) != bg
        && img.at<cv::Vec3b>(c.first + 1, c.second - 1) != color 
        ) {
            std::pair<int,int> n = std::make_pair(c.first, c.second - 1);
            stack.push(n);
        }
    } 
    return pixels;
}

std::list<std::vector<std::pair<int, int>>> indexAndColor(cv::Mat &img, cv::Vec3b bg) {
    std::list<std::vector<std::pair<int,int>>> objectList;

    for (int i = 0; i < img.rows - 1; i++) {
        for (int j = 0; j < img.cols - 1; j++) {
            if (img.at<cv::Vec3b>(i,j) == bg) {
                std::pair<int, int> start = std::make_pair(i,j);
                cv::Vec3b color = cv::Vec3b((rand() % 255), (rand() % 255), (rand() % 255));
                objectList.push_back(indexObject(img, start, bg, color));
            }
        }
    }

    return objectList;
}

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    cv::Vec3b bg = cv::Vec3b(0, 0, 0);

    std::list<std::vector<std::pair<int, int>>> objectList = indexAndColor(img, bg); 

    cv::imshow("Index", img);
    cv::waitKey(0);
     
    return 0;
}