// streaming to another ffmpeg stream:
// https://stackoverflow.com/questions/72884815/how-to-stream-frames-from-opencv-c-code-to-video4linux-or-ffmpeg
#include "beamng/cameraReceiver.h" 

#include <iostream>

CameraReceiver::CameraReceiver(std::string url) 
    : url(url) {}

CameraReceiver::~CameraReceiver() {
    cap.release();
}

bool CameraReceiver::init() {
    // https://docs.opencv.org/3.4/d4/d15/group__videoio__flags__base.html
    // https://opencv.org/blog/reading-and-writing-videos-using-opencv/
    if (!cap.open(url, cv::CAP_FFMPEG)) {
        std::cerr << "[Camera] Failed to open stream: " << url << std::endl;
        return false;
    }
    std::cout << "[Camera] Opened camera stream." << std::endl;
    return true;
}

bool CameraReceiver::poll() {
    cv::Mat frame;

    if (!cap.read(frame)) {
        return false;
    }

    last_frame = frame;
    return true;
}

const cv::Mat& CameraReceiver::getLastFrame() const { 
    return last_frame;
}