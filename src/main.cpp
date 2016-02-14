#include <iostream>
#include <cstring>
#include "rtt/RttTcpServer.h"
#include "rtt/RttTcpClient.h"


void usage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "<appName> -s <port>" << std::endl;
    std::cout << "<appName> -c <ip> <port>" << std::endl;
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
    if (argc == 3 && !strncmp(argv[1], "-s", strlen("-s"))) {
        RttTcpServer server(atoi(argv[2]));
        server.start();
    } else if (argc == 4 && !strncmp(argv[1], "-c", strlen("-c"))) {
        RttTcpClient client(std::string(argv[2]), atoi(argv[3]));
        client.start();
    }

    usage();
}