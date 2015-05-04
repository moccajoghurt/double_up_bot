#include <Windows.h>
#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
	
	cv::Mat a = cv::imread("dealer.png"), b = cv::imread("dealer1.png"), c = cv::imread("no_deal.png"); // num of rows/cols/channels does not matter, they just have to be equal for both

	double dist = norm(a,b,cv::NORM_L2);
	double dist1 = norm(a,c,cv::NORM_L2);
	std::cout << dist << " " << dist1 << std::endl;
	
}