
#ifndef UI_H
#define UI_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

struct Result {
    std::string text;
    cv::Rect boundingBox;
};

class UI {
public:
    void displayFrame(const cv::Mat& frame, const std::vector<Result>& results);
};

#endif // UI_H
