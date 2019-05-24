#include <opencv2/viz.hpp>
#include <iostream>

int main()
{
	cv::viz::Viz3d window("Viz test");
	while(!window.wasStopped()) {
		window.spinOnce(1,true);
	}
	return 0;
}
