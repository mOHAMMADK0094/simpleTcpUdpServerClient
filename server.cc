#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include "server.h"

int createTCPServer(int port)
{
    int serverSocket;
    if (!(serverSocket = socket(AF_INET,SOCK_STREAM,0))){
        std::cerr << "Failed to create server socket.\n";
        return -1;}
    struct sockaddr_in serverAddress,clientAddress;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if(bind(serverSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress)) < 0){
        std::cerr << "Failed to bind socket\n";
        return -1;
    }

    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Failed to listen for connections\n";
        return -1;
    }

    std::cout << "Listening on port 8080...\n";
    int clientSocket;
    socklen_t clientAddressSize = sizeof(clientAddress);
    clientSocket = accept(serverSocket,(struct sockaddr*) &clientAddress , &clientAddressSize);
    std::cout << "Accepted connection from client fd is: " <<  clientSocket << "\n" ;
    char buffer[1024];
    
    while(true) {
        read(clientSocket,buffer,sizeof(buffer));
        std::cout << "Client: " << buffer << std::endl;

        if (strncmp(buffer,"exit",4)==0)
            break;
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}

int createUDPServer(int port){
    int serverSocket;
    if (!(serverSocket = socket(AF_INET,SOCK_DGRAM,0))){
        std::cerr << "Failed to create server socket.\n";
        return -1;}
    struct sockaddr_in serverAddress,clientAddress;

    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if(bind(serverSocket,(struct sockaddr *)&serverAddress,sizeof(serverAddress)) < 0){
        std::cerr << "Failed to bind socket\n";
        return -1;}

    char buffer[1024];
    socklen_t len;
    len=sizeof(clientAddress);
    while(true) {
        memset(buffer,0,sizeof(buffer));
        recvfrom(serverSocket,(char *)buffer,sizeof(buffer),MSG_WAITALL,(struct sockaddr*)&clientAddress,&len);
        std::cout << "Client: " << buffer << std::endl;

        if (strncmp(buffer,"exit",4)==0)
            break;
    }

    close(serverSocket);
    return 0;
}