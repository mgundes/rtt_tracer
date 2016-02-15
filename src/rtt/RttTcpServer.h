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
    void stop(int arg);

private:
    bool work();
    bool readRequestSendResponse(int clientSocketFd);
    bool handleClientConnection(int serverSockFd);
    int _port;
    bool _threadActive;
};


#endif //NETWORK_DIAGNOSTICS_RTTTCP_H
