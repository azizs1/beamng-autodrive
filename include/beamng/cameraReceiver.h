#pragma once

#include <opencv2/opencv.hpp>

class CameraReceiver {
public:
    /* Ctor */
    CameraReceiver(std::string url);
    
    /* Dtor */
    ~CameraReceiver();

    /* 
    * Binds to ffmpeg UDP broadcast
    * @return connection successful or not
    */
    bool init();

    /* 
    * Polls for frames
    * @return whether a frame was received
    */
    bool poll();
    
    /*
    * Getter for last frame
    * @return most recent frame from camera stream
    */
    const cv::Mat& getLastFrame() const;

private:
    // ffmpeg url
    std::string url;
    
    // video capture https://docs.opencv.org/3.4/d8/dfe/classcv_1_1VideoCapture.html
    cv::VideoCapture cap; 
    
    // last frame
    cv::Mat last_frame;
};