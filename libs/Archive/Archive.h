#pragma once

#include <string>
#include <opencv2/core.hpp>

class Archive {
public:
    static bool save(const cv::Mat& frame, const std::string& qrText, const std::string& timestamp = "");
    static int getTotalScans();
    static bool clearLogs();

private:
    Archive() = delete;
};
