#include "Scanner.h"
#include <ZXing/ReadBarcode.h>
#include <ZXing/DecodeHints.h>
#include <ZXing/TextUtfEncoding.h>
#include <ZXing/ImageView.h>
#include <ZXing/BarcodeFormat.h>
#include <opencv2/imgproc.hpp>

Scanner::Scanner()
    : hints(std::make_unique<ZXing::DecodeHints>())
{
    // Enable more exhaustive search and restrict to QR codes
    hints->setTryHarder(true);
    hints->setFormats(ZXing::BarcodeFormat::QR_CODE);
}

Scanner::~Scanner() = default;

std::vector<ScanResult> Scanner::scan(const cv::Mat& frame)
{
    cv::Mat gray;
    // Convert to grayscale if needed
    if (frame.channels() == 3) {
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    } else if (frame.channels() == 4) {
        cv::cvtColor(frame, gray, cv::COLOR_BGRA2GRAY);
    } else {
        gray = frame;
    }

    // Wrap image data for ZXing
    ZXing::ImageView imageView(
        gray.data,
        gray.cols,
        gray.rows,
        ZXing::ImageFormat::Lum8
    );

    // Perform barcode detection
    auto results = ZXing::ReadBarcodes(imageView, *hints);

    std::vector<ScanResult> scanResults;
    for (const auto& result : results) {
        if (result.isValid()) {
            scanResults.emplace_back(convertResult(result));
        }
    }
    return scanResults;
}

ScanResult Scanner::convertResult(const ZXing::Result& result) const
{
    ScanResult res;
    // Extract decoded text as UTF-8 string
    res.text = ZXing::TextUtfEncoding::ToUtf8(result.text());
    // Convert barcode format enum to string
    res.format = ZXing::ToString(result.format());
    // Convert detection points
    res.points = convertPoints(result.position());
    return res;
}

std::vector<cv::Point> Scanner::convertPoints(const std::vector<ZXing::ResultPoint>& zxingPoints) const
{
    std::vector<cv::Point> points;
    points.reserve(zxingPoints.size());
    for (const auto& p : zxingPoints) {
        points.emplace_back(
            static_cast<int>(p.x()),
            static_cast<int>(p.y())
        );
    }
    return points;
}
