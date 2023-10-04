#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;


/////////////////  Color Detection  //////////////////////

Mat imgHSV,mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	namedWindow("TrackBars", (640, 200));
	createTrackbar("Hue Min", "TrackBars", &hmin, 179); // limit <=179
	createTrackbar("Hue Max", "TrackBars", &hmax, 179); // limit <=179
	createTrackbar("Sat Min", "TrackBars", &smin, 255); // limit <=255
	createTrackbar("Sat Max", "TrackBars", &smax, 255); // limit <=255
	createTrackbar("Val Min", "TrackBars", &vmin, 255); // limit <=255
	createTrackbar("Val Max", "TrackBars", &vmin, 255); // limit <=255

	 
	while (true)
	{
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image Mask", mask);

		waitKey(1);

	}
	


	
}
