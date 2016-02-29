#include <iostream>
#include <cstring>
#include "rtt/RttTcpServer.h"
#include "rtt/RttTcpClient.h"
#include "utils/Logger.h"
#include <csignal>
#include <boost/program_options.hpp>

#ifndef RTT_TRACER_VERSION
#define RTT_TRACER_VERSION "0.1"
#endif

namespace po = boost::program_options;

void parse()
{
    po::options_description desc("Rtt Tracer Options");
    desc.add_options()
            ("server", "run as server")
            ("client", "run as client")
            ("port", po::value<int>()->default_value(5600), "port")
            ("ip", po::value<std::string>()->default_value("127.0.0.1"), "client connect ip");
}

void usage()
{
    LOG_WARNING << "Rtt Tracer (v " << RTT_TRACER_VERSION << ") Usage:" << std::endl;
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

    if (argc == 1) {
        usage();
    } else if ( argc >= 2 &&
                (!strncmp(argv[1], "-v", strlen("-v")) || !strncmp(argv[1], "--version", strlen("--version"))) ) {
        std::cout << "Version: " << RTT_TRACER_VERSION << std::endl;
        exit(EXIT_SUCCESS);
    }

    LOG_INFO << "RTT Tracer version " << RTT_TRACER_VERSION << " starting.." << std::endl;

    if (argc == 3 && !strncmp(argv[1], "-s", strlen("-s"))) {
        RttTcpServer server(atoi(argv[2]));
        server.start();
    } else if (argc == 4 && !strncmp(argv[1], "-c", strlen("-c"))) {
        RttTcpClient client(std::string(argv[2]), atoi(argv[3]));
        client.start();
    } else {
        usage();
    }

    Logger::deInit();
}
