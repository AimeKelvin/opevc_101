#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <filesystem>
#include <iostream>

using namespace cv;
using namespace cv::face;
using namespace std;
namespace fs = std::filesystem;

int main() {
    vector<Mat> images;
    vector<int> labels;

    string dataset_path = "./faces_dataset";

    for (auto& entry : fs::directory_iterator(dataset_path)) {
        if (entry.is_directory()) {
            int label = stoi(entry.path().filename().string());
            for (auto& img_path : fs::directory_iterator(entry.path())) {
                Mat img = imread(img_path.path().string(), IMREAD_GRAYSCALE);
                if (!img.empty()) {
                    images.push_back(img);
                    labels.push_back(label);
                }
            }
        }
    }

    Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
    model->train(images, labels);
    model->save("face_model.yml");
    cout << "Model trained and saved!\n";
    return 0;
}
