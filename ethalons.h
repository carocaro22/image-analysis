#include <opencv2/opencv.hpp>
#include "indexing.h"
#include "features.h"
#include <stdio.h>

std::pair<double, double> ethalon(cv::Mat img, std::vector<std::vector<std::pair<int,int>>> & objects, int lower_bound, int upper_bound);

std::vector<std::pair<std::string, std::pair<double, double>>> ethalons(cv::Mat & img, std::list<std::vector<std::pair<int, int>>> & objects);

std::string classify(double f1, double f2, std::vector<std::pair<std::string, std::pair<double, double>>> e);

cv::Mat plt_ethalons(std::vector<std::pair<cv::Scalar, std::pair<double, double>>> data); 

int classifyAndPlot(); 

