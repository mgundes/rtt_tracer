//
// Created by mgundes on 14.02.2016.
//

#ifndef NETWORK_DIAGNOSTICS_RTTTCPCLIENT_H
#define NETWORK_DIAGNOSTICS_RTTTCPCLIENT_H


#include <string>

class RttTcpClient {
public:
    RttTcpClient(std::string ipAddr, int port);
    ~RttTcpClient() {}
    void start();

private:
    bool work();
    bool sendRequestReadResponse(int socketFd);
    long _sequenceNumber;
    int _port;
    std::string _ipAddr;
};


#endif //NETWORK_DIAGNOSTICS_RTTTCPCLIENT_H
