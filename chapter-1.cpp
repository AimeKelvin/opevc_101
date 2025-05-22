#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/*          Image Import 

int main() {
    Mat img = imread("./Resources/test.jpg");
    if (img.empty()) {
        cout << "Image not loaded!" << endl;
        return -1;
    }
    imshow("Original", img);
    waitKey(0);
    return 0;
}
*/


/*        Video 
int main(){

    string path = "Resources/video.webm";
    VideoCapture cap(path);
    Mat img = imread(path);

    while(true){
    cap.read(img);
    imshow("Image", img);
    waitKey(100);
    }
}
*/


//       WebCam

int main(){

    
    VideoCapture cap(0);
    Mat img;

    while(true){
    cap.read(img);
    imshow("Image", img);
    waitKey(1);
    }
}