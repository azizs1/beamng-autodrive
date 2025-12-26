#pragma once

#include "structs/motionSimPacket.h"

class MotionSimReceiver {
public:
    /* Ctor */
    MotionSimReceiver(int port);
    
    /* Dtor */
    ~MotionSimReceiver();

    /* 
    * Binds to BeamNG's MotionSIm UDP broadcast
    * @return connection successful or not
    */
    bool init();

    /* 
    * Polls for basic vehicle motion info
    * @return whether a good packet was received
    */
    bool poll();
    
    /*
    * Getter for last packet
    * @return most recent MotionSimPacket
    */
    const MotionSimPacket& getLastPacket() const;

private:
    // MotionSim port
    int port;
    
    // MotionSim sockfd
    int sockfd;
    
    // store most recent packet
    MotionSimPacket last_packet;
};