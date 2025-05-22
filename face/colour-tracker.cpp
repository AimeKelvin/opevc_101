#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Cannot open camera\n";
        return -1;
    }

    namedWindow("Trackbars", (640, 200));
    
    // Create trackbars to adjust HSV range
    int lowH = 0, highH = 179;
    int lowS = 50, highS = 255;
    int lowV = 50, highV = 255;

    createTrackbar("LowH", "Trackbars", &lowH, 179);
    createTrackbar("HighH", "Trackbars", &highH, 179);
    createTrackbar("LowS", "Trackbars", &lowS, 255);
    createTrackbar("HighS", "Trackbars", &highS, 255);
    createTrackbar("LowV", "Trackbars", &lowV, 255);
    createTrackbar("HighV", "Trackbars", &highV, 255);

    Mat frame, hsv, mask;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // Threshold the HSV image to get only selected colors
        inRange(hsv, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), mask);

        // Morphological operations to remove small noise
        erode(mask, mask, Mat(), Point(-1, -1), 2);
        dilate(mask, mask, Mat(), Point(-1, -1), 2);

        // Find contours
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (auto &contour : contours) {
            if (contourArea(contour) > 1000) { // Filter small areas
                Rect bound = boundingRect(contour);
                rectangle(frame, bound, Scalar(0, 255, 0), 2);
                putText(frame, "Tracked Color", Point(bound.x, bound.y - 10),
                        FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            }
        }

        imshow("Original", frame);
        imshow("Mask", mask);

        if (waitKey(30) == 27) break; // ESC key to quit
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
