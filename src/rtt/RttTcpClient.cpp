//
// Created by mgundes on 14.02.2016.
//

#include "RttTcpClient.h"
#include "LogManager.h"

//
// Created by mgundes on 14.02.2016.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include "RttPayload.h"
#include "../utils/TimeUtils.h"
#include<arpa/inet.h> //inet_addr

RttTcpClient::RttTcpClient(std::string ipAddr, int port)
        : _ipAddr(ipAddr), _port(port), _sequenceNumber(1)
{

}

void RttTcpClient::start()
{
    LOG(INFO) << "Running in Client Mode, connect to " << _ipAddr << ":" << _port << std::endl;
    work();
}

bool RttTcpClient::work() {
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0) {
        LOG(ERROR) << "Error on socket create!" << std::endl;
        return false;
    }

    struct hostent* server = gethostbyname(_ipAddr.c_str());
    if (!server) {
        LOG(ERROR) << "Error regarding server ip!" << std::endl;
        return false;
    }

    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(_ipAddr.c_str());
    serverAddr.sin_port = htons(_port);

    if (connect(sockFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        LOG(ERROR) << "Error on connect! " << std::endl;
        perror("Connect error: ");
        return false;
    }

    while(true) {
        if (!sendRequestReadResponse(sockFd)) {
            LOG(ERROR) << "Error, exiting.." << std::endl;
            break;
        }
        _sequenceNumber++;
        usleep(1*1000000);
    }
    
    close(sockFd);
    return true;
}

bool RttTcpClient::sendRequestReadResponse(int socketFd)
{
    RttPayload sendPayload(_sequenceNumber);
    if (send(socketFd, &sendPayload, sizeof(sendPayload), 0) < 0) {
        LOG(ERROR) << "Error on sending payload!" << std::endl;
        return false;
    }
    LOG(DEBUG) << "Sent seq " << sendPayload.getSequenceNumber() << ", local time(ms) " << sendPayload.getLocalTimeInMS() << std::endl;

    RttPayload readPayload;
    if (read(socketFd, &readPayload, sizeof(readPayload)) < 0) {
        LOG(ERROR) << "Error on reading payload!" << std::endl;
        return false;
    }

    long currentTimeMs = TimeUtils::GetCurrentTimeStampMilliSecond();
    long rttDurationMs = currentTimeMs - sendPayload.getLocalTimeInMS();
    long serverReceiveDuration = readPayload.getLocalTimeInMS() - sendPayload.getLocalTimeInMS();
    long clientReceiveDuration = currentTimeMs - readPayload.getLocalTimeInMS();

    if (readPayload.getSequenceNumber() == sendPayload.getSequenceNumber() &&
        readPayload.getRemoteTimeInMS() == sendPayload.getLocalTimeInMS())
    {
        LOG(INFO) << "Msg " << readPayload.getSequenceNumber() << ", RTT: " << rttDurationMs
                  << ", TransmitDuration: " << serverReceiveDuration
                  << ", ReceiveDuration: " << clientReceiveDuration << std::endl;
        return true;
    }

    LOG(ERROR) << "Error on send and received sequence number!" << std::endl;
    return false;
}
