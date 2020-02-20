#include "MyBGSubtractorMOG2.hpp"

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

MyBGSubtractorMOG2::MyBGSubtractorMOG2(VideoCapture vc, double thresh) {

	cap = vc;

	// inicialización del modelo del fondo
	//...

	mog2 = createBackgroundSubtractorMOG2();
	mog2->setVarThreshold(thresh);
}

void MyBGSubtractorMOG2::LearnModel() {
	
	Mat frame, bgmask;
	namedWindow("Capturando modelo del fondo");
	cout << "Iniciando la actualización del modelo de fondo (método MOG2)" << endl;
	
	for (;;)
	{
		cap >> frame;
		if (frame.empty())
		{
			printf("No puedo leer imagen de la fuente de video\n");
			continue;
		}
		int c = cvWaitKey(40);
		if (c == ' ')
		{
			cout << "Se ha completado la actualización del modelo del fondo" << endl;
			break;
		}
		
		// actualizar el modelo
		// ...
		mog2->apply(frame, bgmask, 0.5);

		imshow("Capturando modelo del fondo",frame);

	}
	destroyWindow("Capturando modelo del fondo");
}

void MyBGSubtractorMOG2::ObtainBGMask(Mat frame, Mat &bgmask) {
	
	// obtener la máscara del fondo
	//...
	mog2->apply(frame, bgmask, 0);
	
	 
}

