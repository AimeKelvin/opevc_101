#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

float w = 250, h = 350;
Mat img, imgWarp;
vector<Point2f> clickedPoints;

// Mouse callback to capture 4 corner points
void mousePoints(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN && clickedPoints.size() < 4) {
        clickedPoints.push_back(Point2f(float(x), float(y)));
        circle(img, Point(x, y), 5, Scalar(0, 255, 0), FILLED);
        imshow("Original", img);

        cout << "Point " << clickedPoints.size() << ": (" << x << ", " << y << ")" << endl;

        // When 4 points are clicked, perform the warp
        if (clickedPoints.size() == 4) {
            Point2f dst[4] = {
                {0.0f, 0.0f},
                {w, 0.0f},
                {0.0f, h},
                {w, h}
            };

            Mat matrix = getPerspectiveTransform(clickedPoints.data(), dst);
            warpPerspective(img, imgWarp, matrix, Point(w, h));

            imshow("Warped Card", imgWarp);
            cout << "Warp complete." << endl;
        }
    }
}

int main() {
    // Load the image (make sure path is correct)
    img = imread("./Resources/cards.png"); // Updated to your uploaded path

    if (img.empty()) {
        cout << "Image not found!" << endl;
        return -1;
    }

    // Set up the mouse callback and show the image
    namedWindow("Original", WINDOW_AUTOSIZE);
    setMouseCallback("Original", mousePoints, nullptr);
    imshow("Original", img);

    cout << "Click on the 4 corners of the card you want to warp (e.g., Queen of Hearts)." << endl;

    waitKey(0);
    return 0;
}
