#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>

using namespace cv;
using namespace cv::face;
using namespace std;

int main() {
    Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
    model->read("face_model.yml");

    CascadeClassifier face_cascade;
    face_cascade.load("./cascades/haarcascade_frontalface_default.xml");

    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Cannot open camera\n";
        return -1;
    }

    Mat frame, gray;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);

        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        for (auto& face : faces) {
            Mat faceROI = gray(face);
            int label;
            double confidence;
            model->predict(faceROI, label, confidence);

            string text = "Aime Kelvin";
            if (confidence < 50) {
                text = "Person " + to_string(label);
            }
            rectangle(frame, face, Scalar(0, 255, 0), 2);
            putText(frame, text, Point(face.x, face.y - 10), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0), 2);
        }

        imshow("Face Recognition", frame);
        if (waitKey(30) == 27) break; // ESC to quit
    }

    cap.release();
    destroyAllWindows();
    return 0;

    
}
