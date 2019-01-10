#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 50

int main(){
    printf("The Server A is up and running using UDP on port 21302.\n");
    
    //Create serv_sock    
    int serv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    //Bind sock with IP address and port number
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  
    serv_addr.sin_port = htons(21302);  
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    while(1){
    //Get ready to receive packet from AWS
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    float buffer[BUF_SIZE];
    //Receive packet from AWS
    int strLen = recvfrom(serv_sock, buffer, BUF_SIZE, 0,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
    printf("The Server A received input <%f>\n",buffer[0]);
    //Calculate the squre of the value
    buffer[0]=buffer[0] * buffer[0];
    printf("The Server A calculated square:<%f>\n",buffer[0]);
    //Send the square to AWS
    sendto(serv_sock, buffer, strLen, 0,(struct sockaddr*)&clnt_addr, clnt_addr_size);
    printf("The Server A finished sending the output to AWS.\n");

    //Receive the square as input from AWS
    strLen = recvfrom(serv_sock, buffer, BUF_SIZE, 0,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
    printf("The Server A received input <%f>\n",buffer[0]);
    //Calculate the squre of the square
    buffer[0]=buffer[0] * buffer[0];
    printf("The Server A calculated square: <%f>\n",buffer[0]);
    //Send the square of square to AWS
    sendto(serv_sock, buffer, strLen, 0,(struct sockaddr*)&clnt_addr, clnt_addr_size);
    printf("The Server A finished sending the output to AWS.\n");
    }
    
    //Close the socket
    close(serv_sock);

    return 0;
}

