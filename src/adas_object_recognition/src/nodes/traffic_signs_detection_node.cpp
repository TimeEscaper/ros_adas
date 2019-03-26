/*
 * Node is in the incubation state.
 */

#include <ros/ros.h>

#include <fstream>
#include <sstream>

#include "detectors/TrafficSignsDetector.h"
#include "utils/ImageProcessingUtils.h"

int main(int argc, char **argv)
{
    ROS_INFO("OpenCV version: %d.%d.%d", CV_VERSION_MAJOR, CV_VERSION_MINOR, CV_VERSION_REVISION);

    TrafficSignsDetector detector;
    std::vector<std::string> testImages;

    std::ifstream inFile(argv[1]);
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.length() != 0) {
            testImages.push_back(line);
        }
    }

    for (auto it = testImages.begin(); it != testImages.end(); ++it) {
        auto image = cv::imread(*it);
        showImage(image);

        auto signs = detector.detect(image);
        if (!signs.empty()) {
            for (auto it = signs.begin(); it != signs.end(); ++it)
                cv::rectangle(image, *it, cv::Scalar(0, 255, 0), 3);
            showImage(image, "Detected signs");
        }
    }

    return 0;
}