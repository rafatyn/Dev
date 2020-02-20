#include "HandGesture.hpp"

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

HandGesture::HandGesture() {
	
}


double HandGesture::getAngle(Point s, Point e, Point f) {
	
	double v1[2],v2[2];
	v1[0] = s.x - f.x;
	v1[1] = s.y - f.y;

	v2[0] = e.x - f.x;
	v2[1] = e.y - f.y;

	double ang1 = atan2(v1[1],v1[0]);
	double ang2 = atan2(v2[1],v2[0]);

	double angle = ang1 - ang2;
	if (angle > CV_PI) angle -= 2 * CV_PI;
	if (angle < -CV_PI) angle += 2 * CV_PI;
	return (angle * 180.0/CV_PI);
}
void HandGesture::FeaturesDetection(Mat mask, Mat output_img) {
	
	vector<vector<Point>> contours;
	Mat temp_mask;
	mask.copyTo(temp_mask);
	int index = -1; //almacena el indice del contorno m�s largo

	// CODIGO 3.1
	// detecci�n del contorno de la mano y selecci�n del contorno m�s largo
	//...
	// mano vac�a
	if (!mask.empty()) {
		findContours(temp_mask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		if (contours.size() > 0) {
			vector<Point> largercontour = contours[0];
			for (int i = 0; i < contours.size(); i++) {
				if (contours[i].size() >= largercontour.size()) {
					index = i;
					largercontour = contours[i];
				}
			}

			if (index != -1) {
				drawContours(output_img, contours, index, cv::Scalar(255, 0, 0), 2, 8, vector<Vec4i>(), 0, Point());
			}
			// pintar el contorno
			//...


			//obtener el convex hull
			vector<int> hull;
			convexHull(contours[index], hull);

			// pintar el convex hull
			Point pt0 = contours[index][hull[hull.size() - 1]];
			for (int i = 0; i < hull.size(); i++)
			{
				Point pt = contours[index][hull[i]];
				line(output_img, pt0, pt, Scalar(0, 0, 255), 2, LINE_AA);
				pt0 = pt;
			}

			//obtener los defectos de convexidad
			vector<Vec4i> defects;
			convexityDefects(contours[index], hull, defects);

			vector<Point> convexdefects,convexstart,convexend;
			int cont = 0;
			for (int i = 0; i < defects.size(); i++) {
				Point s = contours[index][defects[i][0]];
				Point e = contours[index][defects[i][1]];
				Point f = contours[index][defects[i][2]];
				float depth = (float)defects[i][3] / 256.0;
				double angle = getAngle(s, e, f);


				// CODIGO 3.2
				// filtrar y mostrar los defectos de convexidad
				//...
				if (depth > 30 && angle < 90 && angle > 20) {
					circle(output_img, f, 5, Scalar(0, 255, 0), 3);
					convexdefects.push_back(f);
					convexstart.push_back(s);
					convexend.push_back(e);
				}
			}
			Rect r = boundingRect(contours[index]);
			double area = 0;
			area = r.width * r.height;

			if (convexdefects.size() == 4) {
				putText(output_img,"5",Point(10,100),FONT_HERSHEY_COMPLEX,3,Scalar(0,0,255),2);
			}else if (convexdefects.size() == 3) {
				putText(output_img, "4", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}else if (convexdefects.size() == 2 && convexdefects[1].x >= convexdefects[0].x - 30) {
				putText(output_img, "3", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}else if (convexdefects.size() == 1 && getAngle(convexstart[0], convexend[0], convexdefects[0]) < 60) {
				putText(output_img, "2", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}else if (convexdefects.size() == 1 && getAngle(convexstart[0], convexend[0], convexdefects[0]) > 60 && convexdefects[0].x - convexend[0].x > 80) {
				putText(output_img, "Bang!!", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}else if (convexdefects.size() == 0 && area > 33000) {
				putText(output_img, "1", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}else if (convexdefects.size() == 0 && area < 33000 && area > 5000) {
				putText(output_img, "0", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}else if (convexdefects.size() == 0 && area < 5000) {
				putText(output_img, "METE LA MANO!!!!", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}else if (convexdefects.size() == 2) {
				putText(output_img, "Spock!", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}else if (convexdefects.size() == 1 && getAngle(convexstart[0], convexend[0], convexdefects[0]) > 60 && convexdefects[0].x - convexend[0].x < 80) {
				putText(output_img, "OK!!", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
			}
		}
		else {
			putText(output_img, "METE LA MANO!!!!", Point(10, 100), FONT_HERSHEY_COMPLEX, 3, Scalar(0, 0, 255), 2);
		}
	}
		
}