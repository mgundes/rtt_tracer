#include <iostream>
#include <cstring>
#include "rtt/RttTcpServer.h"
#include "rtt/RttTcpClient.h"
#include <csignal>
#include "LogManager.h"

#ifndef RTT_TRACER_VERSION
#define RTT_TRACER_VERSION "0.1"
#endif

void usage()
{
    LOG(WARNING) << "Rtt Tracer (v " << RTT_TRACER_VERSION << ") Usage:" << std::endl;
    LOG(WARNING) << "<appName> -s <port>" << std::endl;
    LOG(WARNING) << "<appName> -c <ip> <port>" << std::endl;
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {

    LogManager logManager;
    if (!logManager.init()) {
        std::cerr << "Logger init failed! Exiting.." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    //TODO: use sigaction for portability
    signal(SIGPIPE, SIG_IGN);

    if (argc == 1) {
        usage();
    } else if ( argc >= 2 &&
                (!strncmp(argv[1], "-v", strlen("-v")) || !strncmp(argv[1], "--version", strlen("--version"))) ) {
        LOG(INFO) << "Version: " << RTT_TRACER_VERSION << std::endl;
        exit(EXIT_SUCCESS);
    }

    LOG(INFO) << "RTT Tracer version " << RTT_TRACER_VERSION << " starting.." << std::endl;

    if (argc == 3 && !strncmp(argv[1], "-s", strlen("-s"))) {
        RttTcpServer server(atoi(argv[2]));
        server.start();
    } else if (argc == 4 && !strncmp(argv[1], "-c", strlen("-c"))) {
        RttTcpClient client(std::string(argv[2]), atoi(argv[3]));
        client.start();
    } else {
        usage();
    }
}
