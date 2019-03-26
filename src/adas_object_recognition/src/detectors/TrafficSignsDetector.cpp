#include "detectors/TrafficSignsDetector.h"
#include "utils/ImageProcessingUtils.h"


std::vector<cv::Rect> TrafficSignsDetector::detect(const cv::Mat &image) {

    cv::Mat sharpImage;
    sharp(image, sharpImage);
    showImage(sharpImage, "Sharp");

    cv::Mat binary;
    hsvFilter(sharpImage, binary);
    showImage(binary, "Binary");

    return std::vector<cv::Rect>();
}


void TrafficSignsDetector::sharp(const cv::Mat &srcBGRIMage, cv::Mat &dstBGRImage) {
    cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                                           1,  1, 1,
            1, -8, 1,
            1,  1, 1);
    cv::Mat imgLaplacian;
    cv::filter2D(srcBGRIMage, imgLaplacian, CV_32F, kernel);
    cv::Mat sharp;
    srcBGRIMage.convertTo(sharp, CV_32F);
    cv::Mat imgResult = sharp - imgLaplacian;
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);

    dstBGRImage = imgResult;
}


void TrafficSignsDetector::hsvFilter(const cv::Mat& srcBGRImage, cv::Mat& dstBinaryImage) {
    cv::Mat hsv;
    cv::cvtColor(srcBGRImage, hsv, CV_BGR2HSV);

    dstBinaryImage = cv::Mat(srcBGRImage.rows, srcBGRImage.cols, CV_8UC1);

    for (int i = 0; i < hsv.rows; i++) {
        for (int j = 0; j < hsv.cols; j++) {

            // OpenCV-specific transform
            cv::Vec3b point = hsv.at<cv::Vec3b>(i, j);
            float hue = point[0] * 2.0f;
            float saturation = point[1] / 256.0f;
            float value = point[2] / 256.0f;

            bool matchRed = false;
            if ((hue <= 20.0f || hue >= 355.0f) && (saturation >= 0.6f))
                matchRed = true;
            else if ((hue <= 30.0f || hue >= 345.0f) && (saturation >= 0.3f)) {
                //matchRed = value <= hue * 0.1f;
                matchRed = false;
            }

            bool matchBlue = false;
            if ((hue >= 220.0f && hue <= 240.0f) && (saturation >= 0.65f))
                matchBlue = true;
            else if ((hue >= 210.0f && hue <= 250.0f) && (saturation >= 0.5f)) {
                //matchBlue = value <= hue * 0.1f;
                matchBlue = false;
            }

            bool matchYellow = false;
            if ((hue >= 40.0f && hue <= 60.0f) && (saturation >= 0.8f))
                matchYellow = true;
            else if ((hue >= 30.0f && hue <= 65.0f) && (saturation >= 0.7f)) {
                if ((hue >= 30.0f && hue <= 65.0f))
                    //matchYellow = value <= hue * 0.1f;
                    matchYellow = false;
                else
                    //matchYellow = value <= hue * 0.2f;
                    matchYellow = false;
            }
            dstBinaryImage.at<uchar>(i, j) = matchRed || matchBlue || matchYellow ? 255 : 0;
        }
    }
}