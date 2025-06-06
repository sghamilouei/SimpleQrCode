//
// Created by sgham on 5/29/2025.
//

#ifndef SCANNER_H
#define SCANNER_H

#include <opencv2/core/mat.hpp>
#include <vector>
#include <string>
#include <memory>

namespace ZXing {
    class DecodeHints;
    class Result;
    class ResultPoint;
}

struct ScanResult {
    std::string text;
    std::string format;
    std::vector<cv::Point> points;
};

class Scanner {
public:
    Scanner();
    ~Scanner();

    std::vector<ScanResult> scan(const cv::Mat& frame);

private:
    std::unique_ptr<ZXing::DecodeHints> hints;

    ScanResult convertResult(const ZXing::Result& result) const;
    std::vector<cv::Point> convertPoints(const std::vector<ZXing::ResultPoint>& zxingPoints) const;
};

#endif // SCANNER_H