#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int main() {
    Mat img = imread("./images/test.jpg");
    if (img.empty()) {
        cout << "Image not loaded!" << std::endl;
        return -1;
    }

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    imshow("Original", img);
    imshow("Grayscale", gray);
    waitKey(0);
    return 0;
}
