// useful references:
// https://www.cs.cmu.edu/~prs/15-441-F10/lectures/r01-sockets.pdf
// https://docs.oracle.com/cd/E19120-01/open.solaris/817-4415/sockets-18552/index.html
#include "beamng/beamngStream.h"

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

BeamNgStream::BeamNgStream(int outGaugePort, int motionSimPort) 
    : og_recv(outGaugePort), ms_recv(motionSimPort) {}
    
bool BeamNgStream::init() {
    if (og_recv.init() && ms_recv.init()) {
        return true;
    }
    return false;
}

void BeamNgStream::poll() {
    og_recv.poll();
    ms_recv.poll();
}

const OutGaugePacket& BeamNgStream::latestOutGauge() const {
    return og_recv.getLastPacket();
}

const MotionSimPacket& BeamNgStream::latestMotionSim() const {
    return ms_recv.getLastPacket();
}

// TODO: need to add for camera, lidar, and others as needed