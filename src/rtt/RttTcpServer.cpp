//
// Created by mgundes on 14.02.2016.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include "RttTcpServer.h"
#include "RttPayload.h"
#include "../utils/Logger.h"
#include "../utils/TimeUtils.h"

RttTcpServer::RttTcpServer(int port)
    : _port(port), _threadActive(false)
{
}

void RttTcpServer::start()
{
    _threadActive = true;
    while (_threadActive) {
        LOG_INFO << "Running in Server Mode, listen port " << _port << std::endl;
        work();
        usleep(2*1000000);
    }
}

void RttTcpServer::stop(int arg)
{
    LOG_INFO << "Stop server.." << std::endl;
    _threadActive = false;
}

bool RttTcpServer::work() {
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        LOG_ERROR << "Error on socket create!" << std::endl;
        return false;
    }

    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(_port);

    if (bind(sockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        LOG_ERROR << "ERROR on binding" << std::endl;
        return false;
    }

    listen(sockFd, 1);

    while(_threadActive) {
        LOG_INFO << "Waiting new connection.." << std::endl;
        struct sockaddr_in clientAddr = {0};
        unsigned int clientAddrLen = sizeof(clientAddr);
        int clientSockFd = accept(sockFd, (struct sockaddr *) &clientAddr, &clientAddrLen);
        std::thread connHandlerThread(&(RttTcpServer::handleClientConnection), clientSockFd, clientAddr);
        if (connHandlerThread.joinable()) {
            LOG_DEBUG << "Detaching thread " << connHandlerThread.get_id() << std::endl;
            connHandlerThread.detach();
        }
    }

    close(sockFd);

    return true;
}

bool RttTcpServer::handleClientConnection(int clientSockFd, struct sockaddr_in clientAddr) {
    LOG_INFO << "Got connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << clientAddr.sin_port << std::endl;
    bool isClientConnected = true;

    while(isClientConnected) {
        if (!readRequestSendResponse(clientSockFd)) {
            LOG_ERROR << "Error on client read/send!" << std::endl;
            break;
        }
    }

    LOG_INFO << "close connection from " << inet_ntoa(clientAddr.sin_addr) << std::endl;
    close(clientSockFd);
    return true;
}

bool RttTcpServer::readRequestSendResponse(int clientSocketFd) {
    RttPayload payload = {0};
    int readBytes = read(clientSocketFd, &payload, sizeof(payload));
    if (readBytes < 0) {
        LOG_ERROR << "Error on read!" << std::endl;
        return false;
    }

    LOG_INFO << "Read: sequence number: " << payload.getSequenceNumber() << ", time milliseconds: " << payload.getLocalTimeInMS() << std::endl;
    payload.setSequenceNumber(payload.getSequenceNumber());
    payload.setRemoteTimeInMS(payload.getLocalTimeInMS());
    payload.setLocalTimeInMS(TimeUtils::getSystemTimeInMilliseconds());

    int sentBytes = send(clientSocketFd, &payload, sizeof(payload), 0);
    if (sentBytes < 0) {
        LOG_ERROR << "Error on send!" << std::endl;
        return false;
    }

    return true;
}
