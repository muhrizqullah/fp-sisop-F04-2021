#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    int valread;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    
    int sock = create_socket();

    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent: %s\n", argv[0]);
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}