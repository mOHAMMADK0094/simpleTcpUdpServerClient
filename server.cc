#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

int main(int argc, char const *argv[])
{
    int serverSocket;
    if (!(serverSocket = socket(AF_INET,SOCK_STREAM,0))){
        std::cerr << "Failed to create server socket.\n";
        return -1;}
    struct sockaddr_in serverAddress,clientAddress;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

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
    
    while(true){

    read(clientSocket,buffer,sizeof(buffer));
    std::cout << "Client: " << buffer << std::endl;

    if (strncmp(buffer,"exit",4)==0)
        break;
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}