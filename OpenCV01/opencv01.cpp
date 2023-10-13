#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

/////////////////  Images  //////////////////////
void DealImg(Mat &img) {
  Mat imgGray, imgBlur, imgCanny, imgDia, imgErode;

  cvtColor(img, imgGray, COLOR_BGR2GRAY);
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
}

int main() {
  bool isOpen;
  VideoCapture cap(0);
  if (!cap.isOpened()) {
    isOpen = false;
    // std::cout << "Failed to open camera with index " << rtsppath <<
    // std::endl;
  } else {
    isOpen = true;
    // cap.set(CAP_PROP_FRAME_WIDTH, 1920);
    // cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
    // cap.set(CAP_PROP_FRAME_WIDTH, 1080);
    // cap.set(CAP_PROP_FRAME_HEIGHT, 720);

    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);

    cap.set(CAP_PROP_FPS, 30);

    cout << "width = " << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "height =" << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
    cout << "fps = " << cap.get(CAP_PROP_FPS) << endl;
  }
  Mat img;
  try {

    while (isOpen) {

      // depend on the value to find object
      {

        cap >> img;
        // findColor(img);
        // DrawPoints(newPoints, myColorValues);
        DealImg(img);
        imshow("img", img);
        if (32 == waitKey(1)) {
          break;
        }
      }
    }
  } catch (const std::exception &e) {
    cout << "exception:" << e.what() << endl;
  }
  cap.release();

  return 0;
}
