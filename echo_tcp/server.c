#include<stdio.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<time.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<errno.h>


int main(){
    int sock0, sock, portnum;
    struct sockaddr_in server;
    struct sockaddr_in client;
    struct timeval tv;
    time_t t;
    struct tm *timeinfo;
    socklen_t len;

    sock0 = socket(AF_INET, SOCK_STREAM, 0); 
    // use IPv4 + TCP and default protocol

    if(sock0 == -1) { 
        // socket create failed

        perror("Socket create error");
        return 1;
    } else { 
        // socket create success

        server.sin_family = AF_INET;
        portnum = 32123;
        server.sin_port = htons(portnum);
        // port number 32123
        // host byte order: little endian
        // network byte order: big endian
        // htons: host to network
        server.sin_addr.s_addr = INADDR_ANY;
        // any IP address can connect to this server
        
        if (bind(sock0, (struct sockaddr *)&server, sizeof(server)) < 0) {
            // bind failed
            perror("Bind failed");

            if (errno == 13){
                // port number is already in use
                printf("Port %d is already in use\n", portnum);
            }
            return 1;
        } else {
            // bind success
            if (listen(sock0, 5) < 0) { // listen to 5 clients
                // listen failed
                perror("Listen failed");
                return 1;
            } else {
                // listen success
                while(1) {
                    printf("Waiting for connection...\n");
                    len = sizeof(client);
                    sock = accept(sock0, (struct sockaddr *)&client, &len);
                    // accept connection from client
                    // sock: socket for communication with client
                    if (sock < 0) {
                        // accept failed
                        perror("Accept failed");
                    } else {
                        printf("from %d:%d\n", ntohs(client.sin_addr.s_addr) ,ntohs(client.sin_port));
                        // ntop: network to presentation
                        // ntohs: network to host short
                        if (gettimeofday(&tv, NULL) < 0) {
                            // get time failed
                            perror("Get time failed");
                        } else {
                            // get time success
                            t = tv.tv_sec;
                            timeinfo = localtime(&t);
                            char *time = asctime(timeinfo);
                            printf("%s\n", asctime(timeinfo));
                            write(sock, time, sizeof(time));
                        }
                    }
                close(sock);
                }
            }
        }
        close(sock0);
    }

    return 0;
}

