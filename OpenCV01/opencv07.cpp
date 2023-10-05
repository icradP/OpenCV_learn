#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Colors Tracker  //////////////////////

void findColor(Mat img) {

}


void main() {
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
		Mat frame;
		while (isOpen)
		{
			cap >> frame;				
			imshow("img", frame);      
			if (32 == waitKey(1))			
			{
				break;
			}
		}
	}
	catch (const std::exception& e)
	{
		cout << "exception:" << e.what() << endl;
	}
	cap.release();

}
