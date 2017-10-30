#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>

#include <stdio.h>
#include <string>
#include <iostream>

#include "MyBGSubtractorColor.hpp"
#include "MyBGSubtractorMOG2.hpp"
#include "HandGesture.hpp"

using namespace std;
using namespace cv;



int main(int argc, char** argv)
{

	Mat frame, bgmask, out_frame;
	


	//Abrimos la webcam

	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		printf("\nNo se puede abrir la camara\n");
		return -1;
	}

	// Creamos las ventanas que vamos a usar en la aplicación

	namedWindow("Reconocimiento");
	namedWindow("Fondo");

	// Aquí hacemos la substracción del fondo para quedarnos con una máscara
	// binaria de la imagen. 

	MyBGSubtractorMOG2 bg_sub_mog2(cap,20);
	//MyBGSubtractorColor bg_sub_color(cap);
	
	//creamos el objeto para el reconocimiento de gestos
	HandGesture hg;

	// iniciamos el proceso de obtención del modelo del fondo

	bg_sub_mog2.LearnModel();
	//bg_sub_color.LearnModel();
	

	for (;;)
	{
		cap >> frame;
		
		if (frame.empty())
		{
			printf("can not read data from the video source\n");
			continue;
		}
		int c = cvWaitKey(40);
		if ((char)c == 'q') break;

		// obtenemos la máscara del fondo con el frame actual
		bg_sub_mog2.ObtainBGMask(frame, bgmask);
		//bg_sub_color.ObtainBGMask(frame, bgmask);
		

		// CODIGO 2.1
		// usar operaciones morfológicas o un filtro de la mediana
		// sobre la imagen para limpiarla de ruido
		//...
		/*
		if (!bgmask.empty()) {
			medianBlur(bgmask, bgmask, 3);
		}*/

		int dilation_size = 3;
		Mat element = getStructuringElement(MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
		
		if (!bgmask.empty()) {
			erode(bgmask, bgmask, element);
			dilate(bgmask, bgmask, element);
		}

		// deteccion del gesto de la mano
		hg.FeaturesDetection(bgmask, frame);

		//outputVideo.write(frame);
		imshow("Reconocimiento", frame);
		imshow("Fondo", bgmask);
		
	}
	
	destroyWindow("Reconocimiento");
	destroyWindow("Fondo");
	cap.release();
	return 0;
}
