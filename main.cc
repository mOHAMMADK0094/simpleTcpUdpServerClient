#include <iostream>
#include <cstring>
#include "server.h"
#include "client.h"

int main(int argc, char const *argv[])
{
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
