#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp> //VideoCapture
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> //cvtColor
#include <opencv2/features2d/features2d.hpp> //ORB
#include <iostream>
#include <vector>

int main() {
	cv::VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}
	cv::Mat frame;

	int count = 0;
	while(cap.read(frame)) {
		if (frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		cv::imshow("raw ", frame);
		const int key = cv::waitKey(1);
		if(key == 'q'/*113*/) break;
		else if(key == 's'/*115*/) {
			std::string filename ="img_"+std::to_string(count)+".png";
			cv::imwrite(filename.c_str(), frame);
			std::cout << "iamge write : " << filename << std::endl;
			count++;
		}
	}

	return 0;
}
