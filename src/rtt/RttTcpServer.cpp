//
// Created by mgundes on 14.02.2016.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "RttTcpServer.h"
#include "RttPayload.h"

RttTcpServer::RttTcpServer(int port)
    : _port(port)
{
}

void RttTcpServer::start()
{
    while (true) {
        std::cout << "Running in Server Mode, listen port " << _port << std::endl;
        work();
    }
}

bool RttTcpServer::work() {
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        std::cerr << "Error on socket create!" << std::endl;
        return false;
    }

    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(_port);

    if (bind(sockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "ERROR on binding" << std::endl;
        return false;
    }

    listen(sockFd, 1);

    struct sockaddr_in clientAddr = {0};
    unsigned int clientAddrLen = sizeof(clientAddr);
    int clientSockFd = accept(sockFd, (struct sockaddr *) &clientAddr, &clientAddrLen);
    if (clientSockFd <0) {
        std::cerr << "Error on client accept!" << std::endl;
        return false;
    }

    std::cout << "Got connection from " << inet_ntoa(clientAddr.sin_addr) << std::endl;

    bool isClientConnected = true;
    while(isClientConnected) {
        if (!readRequestSendResponse(clientSockFd)) {
            break;
        }
    }

    close(clientSockFd);
    close(sockFd);

    return true;
}

bool RttTcpServer::readRequestSendResponse(int clientSocketFd) {
    RttPayload payload = {0};
    int readBytes = read(clientSocketFd, &payload, sizeof(payload));
    if (readBytes < 0) {
        std::cerr << "Error on read!" << std::endl;
        return false;
    }

    std::cout << "Read: sequence number: " << payload.getSequenceNumber() << ", time milliseconds: " << payload.getTimeInMS() << std::endl;
    payload.setSequenceNumber(payload.getSequenceNumber());

    int sentBytes = send(clientSocketFd, &payload, sizeof(payload), 0);
    if (sentBytes < 0) {
        std::cerr << "Error on send!" << std::endl;
        return false;
    }

    return true;
}
