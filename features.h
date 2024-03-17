#include <utility>
#include <vector>
#include <opencv2/opencv.hpp>

float m(std::vector<std::pair<int,int>>obj, float p, float q); 
float area(std::vector<std::pair<int,int>> obj);
std::pair<float,float> center_of_mass(std::vector<std::pair<int,int>> obj);
int circumference(cv::Mat img, std::vector<std::pair<int, int>> obj);
float mu(std::vector<std::pair<int,int>> obj, float p, float q);
float feature1(cv::Mat img, std::vector<std::pair<int,int>> obj);
std::pair<float, float> feature2(std::vector<std::pair<int, int>> o);