//
// Created by mgundes on 14.02.2016.
//

#ifndef NETWORK_DIAGNOSTICS_RTTTCP_H
#define NETWORK_DIAGNOSTICS_RTTTCP_H


#include <string>

class RttTcpServer {
public:
    RttTcpServer(int port);
    ~RttTcpServer() {}
    void start();

private:
    bool work();
    bool readRequestSendResponse(int clientSocketFd);
    int _port;
};


#endif //NETWORK_DIAGNOSTICS_RTTTCP_H
