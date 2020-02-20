#include "MyBGSubtractorColor.hpp"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;




MyBGSubtractorColor::MyBGSubtractorColor(VideoCapture vc) {

	cap = vc;
	max_samples = MAX_HORIZ_SAMPLES * MAX_VERT_SAMPLES;
	
	lower_bounds = vector<Scalar>(max_samples);
	upper_bounds = vector<Scalar>(max_samples);
	means = vector<Scalar>(max_samples);
	
	h_low = 12;
    h_up = 7;
	l_low = 30;
	l_up = 40;
	s_low = 80;
	s_up = 80;

	
	namedWindow("Trackbars");

	createTrackbar("H low:", "Trackbars", &h_low, 100, &MyBGSubtractorColor::Trackbar_func);
	createTrackbar("H high:", "Trackbars", &h_up, 100, &MyBGSubtractorColor::Trackbar_func);
	createTrackbar("L low:", "Trackbars", &l_low, 100, &MyBGSubtractorColor::Trackbar_func);
	createTrackbar("L high:", "Trackbars", &l_up, 100, &MyBGSubtractorColor::Trackbar_func);
	createTrackbar("S low:", "Trackbars", &s_low, 100, &MyBGSubtractorColor::Trackbar_func);
	createTrackbar("S high:", "Trackbars", &s_up, 100, &MyBGSubtractorColor::Trackbar_func);


}

void MyBGSubtractorColor::Trackbar_func(int, void*)
{

}



void MyBGSubtractorColor::LearnModel() {


	
	Mat frame, tmp_frame, hls_frame;
	std::vector<cv::Point> samples_positions;

	cap >> frame;

	//almacenamos las posiciones de las esquinas de los cuadrados 
	Point p;
	for (int i = 0; i < MAX_HORIZ_SAMPLES; i++) {
		for (int j = 0; j < MAX_VERT_SAMPLES; j++) {
			p.x = frame.cols / 2 + (-MAX_HORIZ_SAMPLES / 2 + i)*(SAMPLE_SIZE + DISTANCE_BETWEEN_SAMPLES);
			p.y = frame.rows / 2 + (-MAX_VERT_SAMPLES / 2 + j)*(SAMPLE_SIZE + DISTANCE_BETWEEN_SAMPLES);
			samples_positions.push_back(p);
		}
	}

	namedWindow("Cubre los cuadrados con la mano y pulsa espacio");

	for (;;) {
		
		flip(frame, frame, 1);
		
		frame.copyTo(tmp_frame);

		//dibujar los cuadrados
		
		for (int i = 0; i < max_samples; i++) {
			rectangle(tmp_frame, Rect(samples_positions[i].x, samples_positions[i].y,
				      SAMPLE_SIZE, SAMPLE_SIZE), Scalar(0, 255, 0), 2);
		}
		
		imshow("Cubre los cuadrados con la mano y pulsa espacio", tmp_frame);
		int c = cvWaitKey(40);
		if (c == ' ')
		{
			break;
		}
		cap >> frame;
	}

	// CODIGO 1.1
	// Obtener las regiones de inter�s y calcular la media de cada una de ellas
	// almacenar las medias en la variable means
	// ...
	cvtColor(frame, hls_frame, CV_BGR2HLS);
	for (int i = 0; i < max_samples; i++) {
		Mat roi = hls_frame(Rect(samples_positions[i].x, samples_positions[i].y,
			SAMPLE_SIZE, SAMPLE_SIZE));
		means[i] = mean(roi);
	}

	

	destroyWindow("Cubre los cuadrados con la mano y pulsa espacio");

}
void  MyBGSubtractorColor::ObtainBGMask(cv::Mat frame, cv::Mat &bgmask) {
	
	
	// CODIGO 1.2
	// Definir los rangos m�ximos y m�nimos para cada canal (HLS) 
	// umbralizar las im�genes para cada rango y sumarlas para
	// obtener la m�scara final con el fondo eliminado
	//...
	Mat dst;
	Mat acc(frame.rows, frame.cols, CV_8U, Scalar(0));
	Mat hls_frame;
	cvtColor(frame, hls_frame, CV_BGR2HLS);
	for (int i = 0; i < max_samples; i++) {
		int tmp_h_low = means[i][0] - h_low;
		int tmp_h_up = means[i][0] + h_up;
		int tmp_l_low = means[i][1] - l_low;
		int tmp_l_up = means[i][1] + l_up;
		int tmp_s_low = means[i][2] - s_low;
		int tmp_s_up = means[i][2] + s_up;

		if (tmp_h_low < 0) {
			tmp_h_low = 0;
		}
		if (tmp_l_low < 0) {
			tmp_l_low = 0;
		}
		if (tmp_s_low < 0) {
			tmp_s_low = 0;
		}
		if (tmp_h_up > 255) {
			tmp_h_up = 255;
		}
		if (tmp_s_up > 255) {
			tmp_s_up = 255;
		}
		if (tmp_l_up > 255) {
			tmp_l_up = 255;
		}

		Scalar low(tmp_h_low, tmp_l_low, tmp_s_low);
		Scalar up(tmp_h_up, tmp_l_up, tmp_s_up);
		cv::inRange(hls_frame, low, up, dst);
		acc += dst;
	}
	acc.copyTo(bgmask);
}
