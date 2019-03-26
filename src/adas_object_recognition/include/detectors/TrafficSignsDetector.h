#ifndef PROJECT_TRAFFICSIGNSDETECTOR_H
#define PROJECT_TRAFFICSIGNSDETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

class TrafficSignsDetector {

private:

    void sharp(const cv::Mat& srcBGRIMage, cv::Mat& dstBGRImage);

    void hsvFilter(const cv::Mat& srcBGRImage, cv::Mat& dstBinaryImage);

public:

    TrafficSignsDetector() = default;
    ~TrafficSignsDetector() = default;

    std::vector<cv::Rect> detect(const cv::Mat& image);

};

#endif //PROJECT_TRAFFICSIGNSDETECTOR_H
