#include <opencv2/opencv.hpp>
#include <vector>
#include <list>
#include <utility>

std::list<std::vector<std::pair<int, int>>> indexAndColor(cv::Mat &img, cv::Vec3b bg);