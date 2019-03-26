#ifndef PROJECT_IMAGEPROCESSINGUTILS_H
#define PROJECT_IMAGEPROCESSINGUTILS_H

#include <opencv2/opencv.hpp>

inline void showImage(const cv::Mat& image, const std::string& title = "Image") {
    cv::namedWindow(title);
    cv::imshow(title, image);
    cv::waitKey();
    cv::destroyWindow(title);
}


#endif //PROJECT_IMAGEPROCESSINGUTILS_H
