#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

int main(int argc, char const *argv[])
{
    int clientSocket;
    if(!(clientSocket = socket(AF_INET,SOCK_STREAM,0))){
        std::cerr << "Failed to create socket\n";
        return -1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    if (connect(clientSocket,(struct sockaddr*)&serverAddress,sizeof(serverAddress)) < 0 ){
        std::cerr << "Failed to connect to server\n";
        return -1;
    }

    char buffer[1024];
    while(true){
    std::cout << "Enter message: ";
    std::cin.getline(buffer,sizeof(buffer));

    write(clientSocket,buffer,sizeof(buffer));
    if (strncmp(buffer,"exit",4)==0)
        break;
    
    }
    close(clientSocket);
return 0;
}