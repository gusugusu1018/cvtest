#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main() {
	cv::VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}
	cv::Mat frame;
	while(cap.read(frame)) {
		if (frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		cv::imshow("raw data", frame);
	}

	return 0;
}

