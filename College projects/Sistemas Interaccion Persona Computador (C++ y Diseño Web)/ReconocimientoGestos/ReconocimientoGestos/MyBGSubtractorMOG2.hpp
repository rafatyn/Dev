#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

class MyBGSubtractorMOG2 {

public:
	
	MyBGSubtractorMOG2(cv::VideoCapture vc, double thresh);
	void LearnModel();
	void ObtainBGMask(cv::Mat frame, cv::Mat &bgmask);

private:

	cv::VideoCapture cap;
	cv::Ptr<cv::BackgroundSubtractorMOG2> mog2;


};
