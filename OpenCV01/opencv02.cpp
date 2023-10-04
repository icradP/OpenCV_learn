#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


///////////////// Basic Functions  //////////////////////

void main() {

	{
		string path = "Resources/test.png";
		Mat img = imread(path);
		Mat imgResize, imgCrop;
		//cout << img.size() << endl;
		//resize(img, imgResize, Size(640,480));
		resize(img, imgResize, Size(), 0.5, 0.5);

		Rect roi(200, 100, 300, 300);
		imgCrop = img(roi);

		imshow("Image", img);
		imshow("Image Resize", imgResize);
		imshow("Image Crop", imgCrop);
	}
	{
		Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
		circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);
		rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
		line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);
		putText(img, "Hello opencv", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 2);
		imshow("Image", img);

	} 
	


	waitKey(0);

}
