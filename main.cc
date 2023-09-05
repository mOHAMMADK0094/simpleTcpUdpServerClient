#include <iostream>
#include <cstring>
#include "server.h"
#include "client.h"

int main(int argc, char const *argv[])
{
    if (argc != 2){
        std::cout << "Usage: " << argv[0] << " ARG" << "\nAvailable ARGS:"
        "\n[1]: ts (Run tcp server)"
        "\n[2]: us (Run udp server)"
        "\n[3]: tc (Connect to tcp server)"
        "\n[4]: uc (Connect to udp server)\n";
        return -1;
        }
    if (strncmp(argv[1], "ts",2)==0){
        std::cout << "Running TCP Server\n";
        createTCPServer(8080);
        }
    else if (strncmp(argv[1], "us",2)==0){
        std::cout << "Running UDP Server\n";
        createUDPServer(8080);
        }
    else if (strncmp(argv[1], "tc",2)==0){
        std::cout << "Connecting to TCP server\n";
        clientTCPConnect(8080);
        }
    else if (strncmp(argv[1], "uc",2)==0){
        std::cout << "Connecting to UDP server\n";
        clientUDPConnect(8080);
        }
    return 0;
}
