#include <utility>
#include <vector>
#include <opencv2/opencv.hpp>

double m(std::vector<std::pair<int,int>>obj, double p, double q); 
double area(std::vector<std::pair<int,int>> obj);
std::pair<double,double> center_of_mass(std::vector<std::pair<int,int>> obj);
int circumference(cv::Mat img, std::vector<std::pair<int, int>> obj);
double mu(std::vector<std::pair<int,int>> obj, double p, double q);
double feature1(cv::Mat img, std::vector<std::pair<int,int>> obj);
double feature2(std::vector<std::pair<int, int>> o);