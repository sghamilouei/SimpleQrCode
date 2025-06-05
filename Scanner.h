#ifndef SCANNER_H
#define SCANNER_H

#include <opencv2/core/mat.hpp>
#include <vector>
#include <string>
#include <memory>

// Forward declaration to avoid including ZXing headers here
namespace ZXing {
    class DecodeHints;
    class Result;
}

struct ScanResult {
    std::string text;       // متن استخراج شده از کد
    std::string format;     // نوع کد (QR, UPC-A, etc.)
    std::vector<cv::Point> points; // نقاط گوشه‌های کد در تصویر
};

class Scanner {
public:
    Scanner();
    ~Scanner();

    // تحلیل تصویر و استخراج کدها
    std::vector<ScanResult> scan(const cv::Mat& frame);

private:
    std::unique_ptr<ZXing::DecodeHints> hints;

    // تبدیل نتایج ZXing به فرمت ScanResult
    ScanResult convertResult(const ZXing::Result& result) const;

    // تبدیل نقاط ZXing به نقاط OpenCV
    std::vector<cv::Point> convertPoints(const std::vector<ZXing::ResultPoint>& zxingPoints) const;
};

#endif // SCANNER_H