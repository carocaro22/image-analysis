#include <opencv2/opencv.hpp>
#include "indexing.h"
#include "features.h"
#include <stdio.h>

void plt(std::vector<std::pair<double, double>> data) {
    cv::Mat image(300, 300, CV_8UC3);
    image.setTo(cv::Scalar(255, 255, 255));

    int width = 300;
    int height = 300;
    double min_value = 0.0;
    double max_value = 1.0;
    double x_scale = static_cast<double>(width) / (max_value - min_value);
    double y_scale = static_cast<double>(height) / (max_value - min_value);


    for (int i = 0; i < data.size(); i++) {
    std::cout << "f1_" << i << ": " << data[i].first << std::endl;
    std::cout << "f2_" << i << ": " << data[i].second << std::endl;
    int x = x_scale * (data[i].first - min_value);
    int y = height - y_scale * (data[i].second - min_value);  

    cv::circle(image, cv::Point(x, y), 5, data[i].first, -1);
    }

    cv::imshow("Graph", image);     
    cv::waitKey(0);
}

std::vector<std::vector<std::pair<int, int>>> select3RandomObjects(std::vector<std::vector<std::pair<int, int>>> objectsvector) {
    std::vector<std::vector<std::pair<int, int>>> randomObjects;
    for (int i = 0; i < 3; i++) {
        int index = rand() % 12;
        randomObjects.push_back(objectsvector[index]);
    } 
    return randomObjects;
}

std::pair<double, double> calculateAverage(std::vector<std::vector<std::pair<int, int>>> cluster, cv::Mat img) {
    double sum_f1 = 0;
    double sum_f2 = 0;

    for (int i = 0; i < cluster.size(); i++) {
        sum_f1 = sum_f1 + feature1(img, cluster[i]); 
        sum_f2 = sum_f2 + feature2(cluster[i]);
    }

    double avg_f1 = sum_f1 / cluster.size();
    double avg_f2 = sum_f2 / cluster.size();

    std::pair<double, double> features; 
    features.first = avg_f1;
    features.second = avg_f2;

    return features;
}

void measureDistance(std::vector<std::vector<std::pair<int, int>>> objectsVector,std::vector<std::pair<double, double>> features, cv::Mat img) {
    while(true) {
        std::vector<std::vector<std::pair<int, int>>> cluster_0;
        std::vector<std::vector<std::pair<int, int>>> cluster_1;
        std::vector<std::vector<std::pair<int, int>>> cluster_2;
        std::vector<std::pair<double, double>> averages;

        for (auto object: objectsVector) {
            double f1_o = feature1(img, object);
            double f2_o = feature2(object);
            std::vector<double> distances;
                for (auto feature: features) {
                    double f1_s = feature.first;
                    double f2_s = feature.second;
                    double distance = std::sqrt(pow(f1_s - f1_o, 2) + pow(f2_s - f2_o, 2)); 
                    distances.push_back(distance);
                }
            
            double min = std::min(distances[0], std::min(distances[1], distances[2]));

            if (min == distances[0]) {
                cluster_0.push_back(object);
            }
            if (min == distances[1]) {
                cluster_1.push_back(object);
            }
            if (min == distances[2]) {
                cluster_2.push_back(object);
            } 
        }

        averages.clear();
        std::pair<double, double> avg_0 = calculateAverage(cluster_0, img);
        std::pair<double, double> avg_1 = calculateAverage(cluster_1, img);
        std::pair<double, double> avg_2 = calculateAverage(cluster_2, img);
        averages.push_back(avg_0);
        averages.push_back(avg_1);
        averages.push_back(avg_2);
        plt(features);
        features = averages;
    }
}

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread("images/train.png", cv::IMREAD_COLOR);
    cv::Vec3b bg = cv::Vec3b(0, 0, 0);
    // Object.point[index].x; Object.point[index].y
    std::list<std::vector<std::pair<int, int>>> objectList = indexAndColor(img, bg);

    std::vector<std::vector<std::pair<int, int>>> objectsVector;

    for (auto object: objectList) {
        objectsVector.push_back(object);
    }

    std::vector<std::vector<std::pair<int, int>>> selectedObjects = select3RandomObjects(objectsVector);
    
    std::vector<std::pair<double, double>> initialValues;

    selectedObjects.clear();
    selectedObjects.push_back(objectsVector[3]);
    selectedObjects.push_back(objectsVector[6]);
    selectedObjects.push_back(objectsVector[10]);

    for (auto object: selectedObjects) {
        double f1 = feature1(img, object);
        double f2 = feature2(object);
        initialValues.push_back(std::make_pair(f1, f2));
    }

    measureDistance(objectsVector, initialValues, img);

    cv::waitKey(0);
    return 0;
}