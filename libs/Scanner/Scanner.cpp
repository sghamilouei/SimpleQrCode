#include "Scanner.h"
#include <ZXing/ReadBarcode.h>
#include <ZXing/DecodeHints.h>
#include <ZXing/Result.h>
#include <ZXing/BarcodeFormat.h>
#include <ZXing/ResultPoint.h>
#include <opencv2/imgproc.hpp>

using namespace ZXing;

Scanner::Scanner() {
    hints = std::make_unique<DecodeHints>();
    hints->setTryHarder(true);
    hints->setTryRotate(true);
    hints->setFormats(BarcodeFormat::Any);
}

Scanner::~Scanner() = default;

std::vector<ScanResult> Scanner::scan(const cv::Mat& frame) {
    std::vector<ScanResult> results;
    
    if (frame.empty()) {
        return results;
    }

    
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

    try {
        auto zxingResults = ReadBarcodes({grayFrame.data, grayFrame.cols, grayFrame.rows, ImageFormat::Gray}, *hints);
        
        for (const auto& zxingResult : zxingResults) {
            if (zxingResult.isValid()) {
                results.push_back(convertResult(zxingResult));
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error during scanning: " << e.what() << std::endl;
    }

    return results;
}

ScanResult Scanner::convertResult(const ZXing::Result& result) const {
    ScanResult scanResult;
    scanResult.text = result.text();
    scanResult.format = ToString(result.format());
    
    if (result.position().size() >= 4) {
        scanResult.points = convertPoints(result.position());
    }
    
    return scanResult;
}

std::vector<cv::Point> Scanner::convertPoints(const std::vector<ZXing::ResultPoint>& zxingPoints) const {
    std::vector<cv::Point> points;
    for (const auto& p : zxingPoints) {
        points.emplace_back(static_cast<int>(p.x()), static_cast<int>(p.y()));
    }
    return points;
}
