//
// Created by mgundes on 14.02.2016.
//

#include "RttTcpClient.h"

//
// Created by mgundes on 14.02.2016.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "RttPayload.h"
#include "../utils/TimeUtils.h"

RttTcpClient::RttTcpClient(std::string ipAddr, int port)
        : _ipAddr(ipAddr), _port(port), _sequenceNumber(1)
{

}

void RttTcpClient::start()
{
    std::cout << "Running in Client Mode, connect to " << _ipAddr << ":" << _port << std::endl;
    work();
}

bool RttTcpClient::work() {
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        std::cerr << "Error on socket create!" << std::endl;
        return false;
    }

    struct hostent* server = gethostbyname(_ipAddr.c_str());
    if (!server) {
        std::cerr << "Error regarding server ip!" << std::endl;
        return false;
    }

    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;

    strncpy(server->h_addr, (char *) &serverAddr.sin_addr.s_addr, server->h_length);
    serverAddr.sin_port = htons(_port);

    if (connect(sockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error on connect!" << std::endl;
        return false;
    }

    while(true) {
        if (!sendRequestReadResponse(sockFd)) {
            std::cerr << "Error, exiting.." << std::endl;
            break;
        }
        _sequenceNumber++;
        usleep(5*1000000);
    }

    return true;
}

bool RttTcpClient::sendRequestReadResponse(int socketFd)
{
    RttPayload sendPayload(_sequenceNumber);
    if (send(socketFd, &sendPayload, sizeof(sendPayload), 0) < 0) {
        std::cerr << "Error on sending payload!" << std::endl;
        return false;
    }
    std::cout << "Sent seq " << sendPayload.getSequenceNumber() << ", time(ms) " << sendPayload.getTimeInMS() << std::endl;

    RttPayload readPayload;
    if (read(socketFd, &readPayload, sizeof(readPayload)) < 0) {
        std::cerr << "Error on reading payload!" << std::endl;
        return false;
    }

    std::cout << "Received seq " << readPayload.getSequenceNumber() << ", time(ms) " << readPayload.getTimeInMS() << std::endl;

    if (readPayload.getSequenceNumber() == sendPayload.getSequenceNumber() &&
        readPayload.getTimeInMS() == sendPayload.getTimeInMS()) {
        std::cout << "Network delay/jitter for msg " << readPayload.getSequenceNumber() << ": "
        << (TimeUtils::getSystemTimeInMilliseconds() - readPayload.getTimeInMS()) << " ms" << std::endl;
    } else {
        std::cerr << "Error on send and received sequence number!" << std::endl;
        return false;
    }

    return true;
}