#pragma once
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>
#include <string>

class Archive {
public:
    bool save(const cv::Mat& frame, const std::string& qrText, const std::string& timestamp = "");

private:
    static constexpr const char* IMAGE_DIR = "scanned_images";
    static constexpr const char* LOG_DIR = "logs";
    static constexpr const char* LOG_FILE = "logs/scan_log.json";
    static constexpr int JSON_INDENT = 4;

    std::string generateTimestamp() const;
    std::string sanitizeFilename(const std::string& text) const;
    bool createDirectories() const;
    bool saveImage(const cv::Mat& frame, const std::string& imagePath) const;
    bool updateLogFile(const nlohmann::json& logEntry) const;
};
