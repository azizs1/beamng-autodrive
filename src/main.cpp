/**
 * @file main.cpp
 * @brief Main file for beamng-autodrive.
 *
 * This file initializes BeamNG streaming and connects to BeamNG, subscribing
 * to available sensors in a main dta polling loop for real-time communication.
*/

#include "beamng/beamngStream.h"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    int og_port = 4444; 
    int ms_port = 4445;
    std::string cam_url = "udp://172.19.9.85:9001";

    BeamNgStream stream(og_port, ms_port, cam_url);

    // bind to streams
    if (!stream.init()) {
        std::cerr << "COULD NOT INITIALIZE BEAMNG DATASTREAM!" << std::endl;
        return 1;
    }

    while (1) {
        stream.poll();

        const OutGaugePacket& og = stream.latestOutGauge();

        std::cout << "[OutGauge] "
                  << "Speed: " << og.speed << " m/s, "
                  << "RPM: " << og.rpm << ", "
                  << "Gear: " << int(og.gear) << std::endl;

        const MotionSimPacket& ms = stream.latestMotionSim();

        std::cout << "[MotionSim] "
                  << "Pos: (" << ms.posX << ", " << ms.posY << ", " << ms.posZ << "), "
                  << "Vel: (" << ms.velX << ", " << ms.velY << ", " << ms.velZ << "), "
                  << "Roll: " << ms.rollPos
                  << " Pitch: " << ms.pitchPos
                  << " Yaw: " << ms.yawPos << "\n";

        const cv::Mat& frame = stream.latestCameraFrame();

        if (frame.empty()) {
            std::cout << "[Camera] No frame!" << std::endl;
        } else {
            cv::Scalar mean_val = cv::mean(frame);
            if (mean_val[0] < 2 && mean_val[1] < 2 && mean_val[2] < 2) { 
                std::cout << "[Camera] Frame is just black!" << std::endl; 
            } else {
                std::cout << "[Camera] Frame OK: "
                        << frame.cols << "x" << frame.rows
                        << " type=" << frame.type()
                        << std::endl;
            }
        }
    }
    
    return 0;
}
