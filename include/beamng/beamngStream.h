#pragma once

#include "beamng/outGaugeReceiver.h"
#include "beamng/motionSimReceiver.h"
#include "beamng/cameraReceiver.h"

#include <opencv2/opencv.hpp>

class BeamNgStream {
public:
    /* Ctor */
    BeamNgStream(int outGaugePort, int motionSimPort, std::string camUrl);
    
    /* Dtor */
    ~BeamNgStream() = default;

    /*
    * Initializes sensors
    * @return whether they initialized successfully
    */
    bool init();
   
    /* Polls sensors */
    void poll();

    /*
    * Getter for last OutGauge packet
    * @return most recent OutGaugePacket
    */
    const OutGaugePacket& latestOutGauge() const;

    /*
    * Getter for last MotionSim packet
    * @return most recent MotionSim
    */
    const MotionSimPacket& latestMotionSim() const;
    
    /*
    * Getter for last camera frame
    * @return most recent frame
    */
    const cv::Mat& latestCameraFrame() const;

private:
    /* Receiver for OutGauge data */
    OutGaugeReceiver og_recv;
    
    /* Receiver for MotionSim data */
    MotionSimReceiver ms_recv;

    /* Receiver for Camera frames */
    CameraReceiver cam_recv;
};