
#include "UI.h"

void UI::displayFrame(const cv::Mat& frame, const std::vector<Result>& results) {
    cv::Mat display = frame.clone();

    for (const auto& result : results) {
        cv::rectangle(display, result.boundingBox, cv::Scalar(0, 255, 0), 2);
        cv::putText(display, result.text, result.boundingBox.tl(),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1);
    }

    cv::imshow("QR Code Scanner", display);
    cv::waitKey(1);
}
