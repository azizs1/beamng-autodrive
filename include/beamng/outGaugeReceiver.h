#pragma once

#include "structs/outGaugePacket.h"

class OutGaugeReceiver {
public:
    /* Ctor */
    OutGaugeReceiver(int port);
    
    /* Dtor */
    ~OutGaugeReceiver();

    /* 
    * Binds to BeamNG's OutGauge UDP broadcast
    * @return connection successful or not
    */
    bool init();

    /* 
    * Polls for basic vehicle info
    * @return whether a good packet was received
    */
    bool poll();
    
    /*
    * Getter for last packet
    * @return most recent OutGaugePacket
    */
    const OutGaugePacket& getLastPacket() const;

private:
    // OutGauge port
    int port;
    
    // OutGauge sockfd
    int sockfd;
    
    // store most recent packet
    OutGaugePacket last_packet;
};