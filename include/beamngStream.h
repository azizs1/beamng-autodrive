#pragma once

#include "outGaugePacket.h"
#include "motionSimPacket.h"

class BeamNGStream {
public:
    /* Ctor */
    BeamNGStream(int outGaugePort, int motionSimPort);
    
    /* Dtor */
    ~BeamNGStream();

    /* 
    * Binds to BeamNG's MotionSim UDP broadcast
    * @return connection successful or not
    */
    bool bindMotionSim();

    /* 
    * Binds to BeamNG's OutGauge UDP broadcast
    * @return connection successful or not
    */
    bool bindOutGauge();
    
    /* Disconnect from currently attached BeamNG */
    void disconnect();
    
    /* 
    * Polls for basic vehicle info
    * @return UDP packet with outgauge data
    */
    OutGaugePacket pollVehicleOutGauge();
    
    /* 
    * Polls for vehicle motion info
    * @return UDP packet with motionsim data
    */
    MotionSimPacket pollVehicleMotionSim();
    
    // TODO: ADD SENSOR STUFF LATER
    // std::string pollVehicleSensors();

private:
    // OutGauge port
    int og_port;

    // MotionSim port
    int ms_port;
    
    // OutGauge sockfd
    int og_sockfd;
    
    // MotionSim sockfd
    int ms_sockfd;
};

// TODO: will need to go back and revamp this using threads because recvfrom might cause issues later as it is blocking