#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

 
/////////////////  Images  //////////////////////

void main() {

	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgGray,imgBlur,imgCanny,imgDia,imgErode;

	cvtColor(img,imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDia, kernel);
	erode(imgDia, imgErode, kernel);

	imshow("Image", img);
	imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dilation", imgDia);
	imshow("Image Erode", imgErode);

	waitKey(0);

}
