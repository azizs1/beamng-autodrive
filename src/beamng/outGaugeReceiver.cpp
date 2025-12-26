// useful references:
// https://www.cs.cmu.edu/~prs/15-441-F10/lectures/r01-sockets.pdf
// https://docs.oracle.com/cd/E19120-01/open.solaris/817-4415/sockets-18552/index.html
// https://beej.us/guide/bgnet/html/split/slightly-advanced-techniques.html#blocking
// beej one in general, section 7.1 (blocking)
#include "beamng/outGaugeReceiver.h"

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

OutGaugeReceiver::OutGaugeReceiver(int port) 
    : port(port), sockfd(-1) {}

OutGaugeReceiver::~OutGaugeReceiver() {
    if (sockfd >= 0) { 
        close(sockfd); 
    }
}
    
bool OutGaugeReceiver::init() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "FAILED TO CREATE OUTGAUGE SOCKET" << std::endl;
        return false;
    }

    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    sockaddr_in saddr{};
    memset(&saddr, '\0', sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*) &saddr, sizeof(saddr)) < 0) {
        std::cerr << "COULD NOT BIND TO OUTGAUGE SOCKET" << std::endl;
        return false;
    }

    std::cout << "Successfully binded OutGauge, port " << port << std::endl;

    return true;
}

bool OutGaugeReceiver::poll() {
    ssize_t recv_bytes = recv(sockfd, &last_packet, sizeof(OutGaugePacket), 0);

    if (recv_bytes == sizeof(OutGaugePacket)) {
        return true;
    }
    return false;
}

const OutGaugePacket& OutGaugeReceiver::getLastPacket() const {
    return last_packet;
}