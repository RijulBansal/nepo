#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BROADCAST_ADDR "255.255.255.255" // Broadcast address for local network

int main() {
    int socket_fd;
    char str1[10];
    struct sockaddr_in server_addr;
    char message[100];
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    // Enable broadcast
    int broadcast_enable = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable));

    bzero(&server_addr, sizeof(server_addr));
    bzero(str1,10);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12348);
    server_addr.sin_addr.s_addr=inet_addr("255.255.255.255");
    //inet_pton(AF_INET, BROADCAST_ADDR, &server_addr.sin_addr);
    while(1)
    {
    	printf("Do you want to send data?");
    	fgets(str1,10,stdin);
    	if(strncmp(str1,"Y",1)==0)
    	{
    	bzero(message,100);
    	fgets(message,100,stdin);
    	sendto(socket_fd, message, strlen(message), 0, (struct sockaddr *)&server_addr, addr_len); 
    	printf("Broadcasted: \%s", message);
    	}
    }

    close(socket_fd);

    return 0;
}