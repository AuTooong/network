#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(){
    int sock;
    struct sockaddr_in server;
    char buff[2048];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET: IPv4, SOCK_STREAM: TCP, 0: IP
    if(sock == -1) {
        // socket failed
        perror("socket failed");
        exit(0);
    } else {
        // socket success
        server.sin_family = AF_INET;
        server.sin_port = htons(32123);
        inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);

        connect(sock, (struct sockaddr *)&server, sizeof(server));

        memset(buff, 0, sizeof(buff));
        read(sock, buff, sizeof(buff));

        printf("Server: );
        close(sock);
    }
    return 0;
}

