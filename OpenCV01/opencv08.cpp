#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

Mat preProcessing(Mat& img) {

	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	//erode(imgDia, imgErode, kernel);
	return imgDil;

}



vector<Point> GetContours(Mat& imgDil , Mat& imgOri) {
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect>boundRect(contours.size());
	string objectType;

	vector<Point> biggest;
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		if (area > 1000) {

			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			if (area > maxArea && conPoly[i].size() == 4) {
				//drawContours(imgOri, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0],conPoly[i][1], conPoly[i][2], conPoly[i][3] };
				maxArea = area;
			}
			cout << conPoly[i].size() << endl;
			
			//rectangle(imgOri, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}
	return biggest;
}

vector<Point> reorder(vector<Point>& points) {
	vector<Point> newPoints;
	vector<int> sumPoints, subPoints;
	for (auto& i : points)
	{
		sumPoints.push_back(i.x + i.y);
		subPoints.push_back(i.x - i.y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

	return newPoints;
}
void drawPoints(Mat& img, vector<Point>& points, Scalar color) {

	for (int i = 0; i < points.size(); i++)
	{
		circle(img, points[i], 10, color, FILLED);
		putText(img, to_string(i), points[i], FONT_HERSHEY_PLAIN, 5, color, 4);
	}


}

Mat getWarp(Mat & img, vector<Point> & points, float width, float height) {

	Point2f src[4] = { points[0],points[1],points[2],points[3] };
	Point2f dst[4] = { {0.0f,0.0f},{width,0.0f},{0.0f,height},{width,height} };
	Mat imgWarp;
	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(width, height));
	return imgWarp;
}


void main() {
	vector<Point> initPoints;
	string path = "Resources/paper.jpg";
	Mat imgOriginal = imread(path);
	resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);


	Mat imgGray, imgBlur, imgCanny, imgDia, imgErode;

		
	//PreProcessing
	Mat imgPre  = preProcessing(imgOriginal);
	//Get Contours 
	initPoints =  GetContours(imgPre ,imgOriginal);
	//drawPoints(imgOriginal, initPoints, Scalar(0, 0, 255));
	vector<Point> docPoints = reorder(initPoints);
	//drawPoints(imgOriginal, docPoints, Scalar(0, 255, 0));
	
	//Warp
	float w = 420;
	float h = 570;
	Mat imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//Crop
	int valCorp = 5;
	Rect roi(valCorp, valCorp, w - (2 * valCorp), h - (2 * valCorp));
	Mat imgCrop = imgWarp(roi);

	imshow("Image Original", imgOriginal);
	imshow("Image Pre", imgPre);
	imshow("Image Warp", imgWarp);
	imshow("Image Crop", imgCrop);


	waitKey(0);

}
