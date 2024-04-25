#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "GET / HTTP/1.1\nHost: localhost\n\n";
   
    char buffer[1024] = {0};
    char method[16], protocol[16], url[1024];
    //line 16 is to intitialize variables

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
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
    
    send(sock , hello , strlen(hello) , 0 );
    printf("GET message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    
    //parse http request and print to client
    sscanf(buffer, "%s %s %s", method, url, protocol);
    printf("Method: %s\nUrl: %s\nProtocol: %s\n", method, url, protocol);
    printf("\nHello, World\n\n");

    return 0;
}
