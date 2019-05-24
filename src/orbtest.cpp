#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> //cvtColor
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <vector>

int main() {
	cv::VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}
	cv::Mat frame, gray;

	cv::Ptr<cv::ORB> detector = cv::ORB::create(5000);
	cv::Ptr<cv::ORB> extractor = cv::ORB::create();
	std::vector<cv::KeyPoint> orbkeypoints;
	cv::Mat descriptors;

	int count = 0;
	while(cap.read(frame)) {
		if (frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		detector->detect(gray,orbkeypoints);
		extractor->compute(gray,orbkeypoints,descriptors);
		std::vector<cv::KeyPoint>::iterator itk;
		for (std::vector<cv::KeyPoint>::iterator itk = orbkeypoints.begin(); itk != orbkeypoints.end(); ++itk) {
			std::cout << itk->pt << std::endl;
			cv::circle(frame, itk->pt, 1, cv::Scalar(0,255,0), -1);
		}
		cv::imshow("orb", frame);
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
