#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define PORT 8080

int create_socket(){
    struct sockaddr_in address;
    int fd;
    int opt = 1;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int isBinding = bind(fd, (struct sockaddr *)&address, sizeof(address));
    if (isBinding != 0)
    {
        fprintf(stderr, "bind failed [%s]\n", strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }

    int isListening = listen(fd, 3);
    if (isListening != 0)
    {
        fprintf(stderr, "listen failed [%s]\n", strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }
    return fd;
}

int main(int argc, char const *argv[]) {
    socklen_t addrlen;
    struct sockaddr_in new_addr;
    pthread_t tid;
    int new_fd, server_fd = create_socket();
    while(1) {
        new_fd = accept(server_fd, (struct sockaddr *)&new_addr, &addrlen);
    }
    int valread;
    char buffer[1024]={0};
    char *hello = "Hello from server";

    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;
}