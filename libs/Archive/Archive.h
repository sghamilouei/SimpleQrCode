//
// Created by M on 6/7/2025.
//

#pragma once

#include <string>
#include <opencv2/core.hpp>

void save_archive(const cv::Mat& frame, const std::string& qr_text, const std::string& timestamp = "");


#endif //ARCHIVE_H
