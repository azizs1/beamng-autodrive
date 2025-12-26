// useful references:
// https://www.cs.cmu.edu/~prs/15-441-F10/lectures/r01-sockets.pdf
// https://docs.oracle.com/cd/E19120-01/open.solaris/817-4415/sockets-18552/index.html
#include "beamngStream.h"

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

BeamNGStream::BeamNGStream(int outGaugePort, int motionSimPort) 
    : og_port(outGaugePort), ms_port(motionSimPort), 
      og_sockfd(-1), ms_sockfd(-1) {}

BeamNGStream::~BeamNGStream() {
    disconnect();
}
    
bool BeamNGStream::bindOutGauge() {
    og_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (og_sockfd < 0) {
        std::cerr << "FAILED TO CREATE OUTGAUGE SOCKET" << std::endl;
        return false;
    }

    sockaddr_in og_saddr{};
    memset(&og_saddr, '\0', sizeof(og_saddr));
    og_saddr.sin_family = AF_INET;
    og_saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    og_saddr.sin_port = htons(og_port);

    if (bind(og_sockfd, (struct sockaddr*) &og_saddr, sizeof(og_saddr)) < 0) {
        std::cerr << "COULD NOT BIND TO OUTGAUGE SOCKET" << std::endl;
        return false;
    }

    return true;
}

bool BeamNGStream::bindMotionSim() {
    ms_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (ms_sockfd < 0) {
        std::cerr << "FAILED TO CREATE MOTIONSIM SOCKET" << std::endl;
        return false;
    }

    sockaddr_in ms_saddr{};
    memset(&ms_saddr, '\0', sizeof(ms_saddr));
    ms_saddr.sin_family = AF_INET;
    ms_saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ms_saddr.sin_port = htons(ms_port);

    if (bind(ms_sockfd, (struct sockaddr*) &ms_saddr, sizeof(ms_saddr)) < 0) {
        std::cerr << "COULD NOT BIND TO MOTIONSIM SOCKET" << std::endl;
        return false;
    }
    
    return true;
}

void BeamNGStream::disconnect() {
    if (og_sockfd >= 0) {
        close(og_sockfd);
        og_sockfd = -1;
    }

    if (ms_sockfd >= 0) {
        close(ms_sockfd);
        ms_sockfd = -1;
    }
}

OutGaugePacket BeamNGStream::pollVehicleOutGauge() {
    // https://documentation.beamng.com/modding/protocols/
    OutGaugePacket og_packet{};
    recvfrom(og_sockfd, &og_packet, sizeof(OutGaugePacket), 0, nullptr, nullptr);
    return og_packet;
}

MotionSimPacket BeamNGStream::pollVehicleMotionSim() {
    https://documentation.beamng.com/modding/protocols/
    MotionSimPacket ms_packet{};
    recvfrom(ms_sockfd, &ms_packet, sizeof(MotionSimPacket), 0, nullptr, nullptr);
    return ms_packet;
}
