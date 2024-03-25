#include <utility>
#include <vector>
#include <opencv2/opencv.hpp>

double m(std::vector<std::pair<int,int>>obj, double p, double q) {
    double sum = 0;
    for (int i = 0; i < obj.size(); i++) {
        double x = obj.at(i).first; 
        double y = obj.at(i).second;
        double x_p = std::pow(x, p);
        double y_q = std::pow(y, q);
        sum = sum + (x_p*y_q);
    }
    return sum;
}

double area(std::vector<std::pair<int,int>> obj) {
    return m(obj, 0, 0); 
}

std::pair<double,double> center_of_mass(std::vector<std::pair<int,int>> obj) {
    double x_t = m(obj, 1, 0) / area(obj);
    double y_t = m(obj, 0, 1) / area(obj);
    return std::pair<double,double>(x_t, y_t);
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

double mu(std::vector<std::pair<int,int>> obj, double p, double q) {
    double x_t = center_of_mass(obj).first;
    double y_t = center_of_mass(obj).second;
    double sum  = 0;
    for (int i = 0; i < obj.size(); i++) {
        int x = obj.at(i).first;
        int y = obj.at(i).second;
        double a = pow((x - x_t), p);
        double b = pow((y - y_t), q);
        double result = a*b;
        sum = sum + result;
    }
    return sum;
}

double feature1(cv::Mat img, std::vector<std::pair<int,int>> obj) {
    double c = circumference(img, obj);
    double a = area(obj);
    double result = pow(c, 2) / (100*a);
    // std::cout << "feature 1: " << result << std::endl;
    return result;
}

double feature2(std::vector<std::pair<int, int>> o) {
    double mu_a = 0.5*(mu(o,2,0) + mu(o,0,2));
    double mu_b = 0.5*(sqrt(4*pow(mu(o,1,1), 2) + pow(mu(o,2,0)-mu(o,0,2), 2)));
    double a = (mu_a - mu_b);
    double b = (mu_a + mu_b);
    double result = a / b; 
    // std::cout << "feature 2: " << result << std::endl;
    return result; 
}