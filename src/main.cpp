#include <iostream>
#include <cstring>
#include "rtt/RttTcpServer.h"
#include "rtt/RttTcpClient.h"
#include "utils/Logger.h"
#include <csignal>

void usage()
{
    LOG_WARNING << "Usage:" << std::endl;
    LOG_WARNING << "<appName> -s <port>" << std::endl;
    LOG_WARNING << "<appName> -c <ip> <port>" << std::endl;
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {

    signal(SIGPIPE, SIG_IGN);
    if (!Logger::init()) {
        std::cerr << "Logger init failed! Exiting.." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (argc == 3 && !strncmp(argv[1], "-s", strlen("-s"))) {
        RttTcpServer server(atoi(argv[2]));
        server.start();
    } else if (argc == 4 && !strncmp(argv[1], "-c", strlen("-c"))) {
        RttTcpClient client(std::string(argv[2]), atoi(argv[3]));
        client.start();
    }

    Logger::deInit();
}
