// This is taken almost directly from https://documentation.beamng.com/modding/protocols/
#pragma once
#include <cstdint>
#include <cstddef>

// https://stackoverflow.com/questions/3318410/pragma-pack-effect
// does not work without this
#pragma pack(push, 1)
struct OutGaugePacket {
    uint32_t time;
    char     car[4];
    uint16_t flags;
    int8_t   gear;
    int8_t   plid;
    float    speed;
    float    rpm;
    float    turbo;
    float    engTemp;
    float    fuel;
    float    oilPressure;
    float    oilTemp;
    uint32_t dashLights;
    uint32_t showLights;
    float    throttle;
    float    brake;
    float    clutch;
    char     display1[16];
    char     display2[16];
    int32_t  id;
};
#pragma pack(pop)
