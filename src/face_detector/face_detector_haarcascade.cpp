#include "face_detector_haarcascade.h"

FaceDetectorHaarCascade::FaceDetectorHaarCascade() {
    setDetectorName("Haar Cascade");
    fs::path FACE_CASCADE_PATH_ABS = fs::absolute(FACE_CASCADE_PATH);
    if( !face_cascade.load(FACE_CASCADE_PATH_ABS.string()) ) {
        std::cout << "Cannot Open Haar Cascade model: " << FACE_CASCADE_PATH << std::endl;
        exit(-1);
    }
}

FaceDetectorHaarCascade::~FaceDetectorHaarCascade() {
}


std::vector<LandMarkResult> FaceDetectorHaarCascade::detect(const cv::Mat & img) {

    cv::Mat gray;
    
    // Convert image to gray (we only need grayscale image in this detector)
    cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // Detect face using loaded model
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces);

    // Convert rect to landmark results;
    std::vector <LandMarkResult> landmark_results; 
    for (size_t i = 0; i < faces.size(); ++i) {

        // Put face into the result only if face does not go out of the boundary of image.
        // This prevent false positive for OpenCV HaarCascade and ResNet10 face detector
        if ( 0 <= faces[i].x && 0 <= faces[i].width && faces[i].x + faces[i].width <= img.cols
        && 0 <= faces[i].y && 0 <= faces[i].height && faces[i].y + faces[i].height <= img.rows) {
            LandMarkResult landmark;
            landmark.setFaceRect(faces[i]);
            landmark_results.push_back(landmark);
        }

    }

    return landmark_results;

}