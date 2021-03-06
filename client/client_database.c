#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080

char pesan[50]={0};

void sqlCreate(int sock){
    char namaDB[50]={"\0"};
    strcat(namaDB,"create_db");
    strcat(namaDB, pesan+15);
    send(sock,namaDB,strlen(namaDB),0);
    printf("SEND %s\n",namaDB);
}

void sqlDrop(int sock){
    char namaDB[50]={"\0"};
    strcat(namaDB,"drop_db");
    strcat(namaDB, pesan+13);
    send(sock,namaDB,strlen(namaDB),0);
    printf("SEND %s\n",namaDB);
    
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // fungsi yg dipakai
    while(1){
        
        gets(pesan);
        // printf("%s", pesan);
        char *token;
        token = strtok(pesan, " ");
        // printf("%s", pesan);
        if(strcmp("CREATE", pesan)==0){
            char buffer[1024] = {0};
            strncat(buffer, pesan+7, 4);
            //printf("buff %s\n", buffer);
            if(strcmp("DATA", buffer)==0){
                sqlCreate(sock);
            }
            if(strcmp("USER", buffer)==0){
                printf("user\n");
            }

        }
        else if (strcmp("DROP", pesan)==0){
            sqlDrop(sock);
        }
        else if (strcmp("EXIT", pesan)==0){
            return 0;
        }
        else send(sock,"gagal",strlen("gagal"),0);
        strcpy(pesan, "");
    }
    return 0;
}
