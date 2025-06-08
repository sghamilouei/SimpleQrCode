#pragma once

#include <string>
#include <opencv2/core.hpp>

class Archive {
public:
    static void save(const cv::Mat& frame, const std::string& qrText, const std::string& timestamp = "");
private:
    Archive() = delete;
};

