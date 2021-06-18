#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

char database_path[100] = "databases/";

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    // fungsi yang dipakai
    while (1)
    {
        char buffer[1024] = {0};
        // printf("BUFFER : %s\n",buffer );
        valread = read( new_socket , buffer,1024 );
        printf("cmd : %s\n",buffer );
        char *token;
        token = strtok(buffer, " ");
        if(strcmp(token, "create_db")==0){
            printf("NAMA : %s\n",buffer+10 );
            token = strtok(buffer+10, " ");
            int child_create = fork();
            if (child_create < 0) exit(EXIT_FAILURE);
            if (child_create == 0) {
                char alamatCreate[50]={"\0"};
                strcat(alamatCreate, database_path);
                // strcat(alamatCreate, "/");
                strcat(alamatCreate, token);
                printf("%s\n", alamatCreate);
                char *argv[] = {"mkdir", "-p", alamatCreate, NULL};
                execv("/bin/mkdir", argv);
            }
        }

        if(strcmp(token, "drop_db")==0){
            printf("NAMA : %s\n",buffer+8 );
            token = strtok(buffer+8, " ");
            int child_create = fork();
            if (child_create < 0) exit(EXIT_FAILURE);
            if (child_create == 0) {
                char alamatCreate[50]={"\0"};
                strcat(alamatCreate, database_path);
                strcat(alamatCreate, token);
                printf("%s\n", alamatCreate);
                char *argv[] = {"rmdir", alamatCreate, NULL};
                execv("/bin/rmdir", argv);
            }
        }
    }
    return 0;
}
