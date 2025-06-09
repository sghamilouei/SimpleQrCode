#include "archive.h"
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>

bool Archive::save(const cv::Mat& frame, const std::string& qrText, const std::string& timestamp) {
    try {
        if (frame.empty()) {
            return false;
        }
        
        if (!createDirectories()) {
            return false;
        }
        
        std::string timeStr = timestamp.empty() ? generateTimestamp() : timestamp;
        std::string safeTimeStr = sanitizeFilename(timeStr);
        
        std::string imageName = "scan_" + safeTimeStr + ".jpg";
        std::filesystem::path imagePath = std::filesystem::path(IMAGE_DIR) / imageName;
        
        if (!saveImage(frame, imagePath.string())) {
            return false;
        }
        
        nlohmann::json logEntry;
        logEntry["timestamp"] = timeStr;
        logEntry["image_path"] = imagePath.string();
        logEntry["qr_text"] = qrText;
        logEntry["image_size"] = {
            {"width", frame.cols},
            {"height", frame.rows}
        };
        
        return updateLogFile(logEntry);
        
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    } catch (const cv::Exception& e) {
        std::cerr << "OpenCV error: " << e.what() << std::endl;
        return false;
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

std::string Archive::generateTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y%m%d_%H%M%S");
    return ss.str();
}

std::string Archive::sanitizeFilename(const std::string& text) const {
    std::string safe = text;
    std::replace(safe.begin(), safe.end(), '/', '_');
    std::replace(safe.begin(), safe.end(), '\\', '_');
    std::replace(safe.begin(), safe.end(), ':', '_');
    std::replace(safe.begin(), safe.end(), '*', '_');
    std::replace(safe.begin(), safe.end(), '?', '_');
    std::replace(safe.begin(), safe.end(), '"', '_');
    std::replace(safe.begin(), safe.end(), '<', '_');
    std::replace(safe.begin(), safe.end(), '>', '_');
    std::replace(safe.begin(), safe.end(), '|', '_');
    return safe;
}

bool Archive::createDirectories() const {
    try {
        std::filesystem::create_directories(IMAGE_DIR);
        std::filesystem::create_directories(LOG_DIR);
        return true;
    } catch (const std::filesystem::filesystem_error&) {
        return false;
    }
}

bool Archive::saveImage(const cv::Mat& frame, const std::string& imagePath) const {
    try {
        std::vector<int> compression_params;
        compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
        compression_params.push_back(95);
        
        return cv::imwrite(imagePath, frame, compression_params);
    } catch (const cv::Exception&) {
        return false;
    }
}

bool Archive::updateLogFile(const nlohmann::json& logEntry) const {
    try {
        std::filesystem::path logFile = LOG_FILE;
        nlohmann::json allLogs;
        
        if (std::filesystem::exists(logFile)) {
            std::ifstream inFile(logFile);
            if (inFile.is_open()) {
                try {
                    inFile >> allLogs;
                } catch (const nlohmann::json::exception&) {
                    allLogs = nlohmann::json::array();
                }
                inFile.close();
            }
        } else {
            allLogs = nlohmann::json::array();
        }
        
        allLogs.push_back(logEntry);
        
        std::ofstream outFile(logFile);
        if (outFile.is_open()) {
            outFile << allLogs.dump(JSON_INDENT);
            outFile.close();
            return true;
        }
        
        return false;
        
    } catch (const std::exception&) {
        return false;
    }
}
