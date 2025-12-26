/**
 * @file main.cpp
 * @brief Main file for beamng-autodrive.
 *
 * This file initializes BeamNG streaming and connects to BeamNG, subscribing
 * to available sensors in a main dta polling loop for real-time communication.
*/

#include "beamngStream.h"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
    int og_port = 4444; 
    int ms_port = 4445;

    BeamNGStream stream(og_port, ms_port);
    std::cout << "sizeof(MotionSimPacket) = " << sizeof(MotionSimPacket) << "\n";
    std::cout << "sizeof(OutGaugePacket) = " << sizeof(OutGaugePacket) << "\n";

    // bind to OutGauge
    if (stream.bindOutGauge()) {
        std::cout << "OUTGAUGE BOUND ON PORT " << og_port << std::endl;
    }

    // bind to MotionSim
    if (stream.bindMotionSim()) {
        std::cout << "MOTIONSIM BOUND ON PORT " << ms_port << std::endl;
    }

    while (1) {
        {
            OutGaugePacket og = stream.pollVehicleOutGauge();

            std::cout << "[OutGauge] "
                      << "Speed: " << og.speed << " m/s, "
                      << "RPM: " << og.rpm << ", "
                      << "Gear: " << int(og.gear) << "\n";
        }

        {
            MotionSimPacket ms = stream.pollVehicleMotionSim();

            std::cout << "[MotionSim] "
                      << "Pos: (" << ms.posX << ", " << ms.posY << ", " << ms.posZ << "), "
                      << "Vel: (" << ms.velX << ", " << ms.velY << ", " << ms.velZ << "), "
                      << "Roll: " << ms.rollPos
                      << " Pitch: " << ms.pitchPos
                      << " Yaw: " << ms.yawPos << "\n";
        }
    }
    
    return 0;
}
