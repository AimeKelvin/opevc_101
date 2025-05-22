#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;


  /////////////// Basic Functions ///////////

int main() {
    Mat img = imread("./Resources/test.jpg");
    Mat imgGray, imgBlur, gray, imgCanny, imgDia, imgErode;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5));
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(7,7),5,0);
    Canny(imgBlur, imgCanny, 25,75);

    dilate(imgCanny, imgDia, kernel);
    erode(imgDia, imgErode, kernel);
    imshow("Original", img);
    imshow("Blurred", imgBlur);
    imshow("DIALATION", imgDia);
    imshow("Erode", imgErode);
    waitKey(0);
    return 0;
}



