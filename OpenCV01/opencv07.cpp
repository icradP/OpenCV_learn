#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Colors Tracker  //////////////////////

//you need limit one colors object to test this .
vector <vector<int>> myColors{ {40,31,0,83,255,255}}; //cat green hsv value
vector <Scalar> myColorValues{ {0,255,0}}; //green

vector<vector<int>> newPoints;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

Mat img;

Point GetContours(Mat imgDil) {
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect>boundRect(contours.size());
	string objectType;

	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		if (area > 1000) {

			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;


			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return myPoint;
}

void findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	//cout << myColors.size() << endl;
	for (int i = 0; i < myColors.size(); i++)
	{
		Mat mask;
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		inRange(imgHSV, lower, upper, mask);
		imshow(to_string(i), mask);
		Point myPoint = GetContours(mask);
		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoints.push_back({ myPoint.x, myPoint.y, i });
		}
	}

}

void DrawPoints(vector<vector<int>>& newPoints, vector <Scalar>& myColorValues) {
	for (int i = 0; i < newPoints.size(); i++)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]],FILLED);
	}

}



void main() {


	namedWindow("TrackBars", (640, 200));
	createTrackbar("Hue Min", "TrackBars", &hmin, 179); // limit <=179
	createTrackbar("Hue Max", "TrackBars", &hmax, 179); // limit <=179
	createTrackbar("Sat Min", "TrackBars", &smin, 255); // limit <=255
	createTrackbar("Sat Max", "TrackBars", &smax, 255); // limit <=255
	createTrackbar("Val Min", "TrackBars", &vmin, 255); // limit <=255
	createTrackbar("Val Max", "TrackBars", &vmin, 255); // limit <=255


	bool isOpen = false;
	string rtsppath = "rtsp://admin:123456@192.168.8.109:8554/live";
	VideoCapture cap(rtsppath);
	if (!cap.isOpened()) {
		isOpen = false;
		std::cout << "Failed to open camera with index " << rtsppath << std::endl;
	}
	else {
		isOpen = true;
		cout << "width = " << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
		cout << "height =" << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
		cout << "fps = " << cap.get(CAP_PROP_FPS) << endl;
	}
	
	try
	{
		
		while (isOpen)
		{
			

#ifdef FIND_COLORS
			//find value
			{
				Mat imgHSV, mask, frame;
				cap >> frame;
				cvtColor(frame, imgHSV, COLOR_BGR2HSV);

				Scalar lower(hmin, smin, vmin);
				Scalar upper(hmax, smax, vmax);
				inRange(imgHSV, lower, upper, mask);
				imshow("img", frame);
				imshow("img HSV", imgHSV);
				imshow("img Mask", mask);
				cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
				if (32 == waitKey(1))
				{
					break;
				}
		}
#else 
			//depend on the value to find object
			{
				
				cap >> img;
				findColor(img);
				DrawPoints(newPoints,myColorValues);
				imshow("img", img);
				if (32 == waitKey(1))
				{
					break;
				}
			}

#endif
		}
	}
	catch (const std::exception& e)
	{
		cout << "exception:" << e.what() << endl;
	}
	cap.release();

}
