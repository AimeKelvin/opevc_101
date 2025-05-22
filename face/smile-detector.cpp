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

    Mat frame, hsv, mask;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Convert to HSV color space
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // Threshold for skin color (this range may need tweaking)
        inRange(hsv, Scalar(0, 48, 80), Scalar(20, 255, 255), mask);

        // Morphological operations to remove noise
        erode(mask, mask, Mat(), Point(-1, -1), 2);
        dilate(mask, mask, Mat(), Point(-1, -1), 2);

        // Find contours
        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        if (contours.size() > 0) {
            // Find largest contour assuming it's the hand
            int largest_idx = 0;
            double max_area = contourArea(contours[0]);
            for (size_t i = 1; i < contours.size(); i++) {
                double area = contourArea(contours[i]);
                if (area > max_area) {
                    max_area = area;
                    largest_idx = i;
                }
            }

            // Draw contour
            drawContours(frame, contours, largest_idx, Scalar(0, 255, 0), 2);

            // Convex hull & defects to count fingers can be added here
            // For now, just show the contour
        }

        imshow("Hand Sign Recognition", frame);
        imshow("Mask", mask);

        if (waitKey(30) == 27) break; // ESC to quit
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
