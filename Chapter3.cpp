#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;


  /////////////// RESIZE AND CROP  ///////////

int main() {
    Mat img = imread("./Resources/test.jpg");
    Mat imgResize, imgCrop;
    cout << img.size() << endl;
    resize(img,imgResize, Size(), 0.5,0.5);
    Rect roi(100, 100,300,250);
    imgCrop = img(roi);
    imshow("Image Original", img);
    imshow("Resize", imgResize);
    imshow("Crop", imgCrop);
    waitKey(0);
    return 0;
}



