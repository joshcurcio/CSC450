#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    uint16_t port = 3000;
    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons (port);
    name.sin_addr.s_addr = htonl (INADDR_ANY);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int bindfd = bind(sockfd, (struct sockaddr *) &name, sizeof(name));
    int listenfd = listen(sockfd, 100);
    printf("Listenning....\n");
    int clientfd = accept(sockfd, (struct sockaddr *) &name, sizeof(name));
    printf("Client Connected....\n");
}