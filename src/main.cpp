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

    BeamNgStream stream(og_port, ms_port);

    // bind to OutGauge
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
    }
    
    return 0;
}
