// This is taken almost directly from https://documentation.beamng.com/modding/protocols/
#pragma once
#include <cstdint>

// https://stackoverflow.com/questions/3318410/pragma-pack-effect
// does not work without this
#pragma pack(push, 1)
struct MotionSimPacket
{
    char format[4];   // always "BNG1"

    float posX, posY, posZ;     // world position
    float velX, velY, velZ;     // velocity
    float accX, accY, accZ;     // acceleration, no gravity

    float upX, upY, upZ;        // "up" vector components

    float rollPos, pitchPos, yawPos;   // orientation angles
    float rollVel, pitchVel, yawVel;   // angular velocities
    float rollAcc, pitchAcc, yawAcc;   // angular accelerations
};
#pragma pack(pop)
