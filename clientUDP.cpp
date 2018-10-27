#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(24302);  //端口
   
    //send to server
    sockaddr fromAddr;
    int addrLen = sizeof(fromAddr);
      socklen_t serv_addr_size = sizeof(serv_addr);
      char str[] = "Hello World!";
      char buffer[40];
      sendto(sock, str,sizeof(str), 0, (struct sockaddr*)&serv_addr, serv_addr_size);
      int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_addr_size);
      buffer[strLen] = 0;
      printf("Message from server: %s\n",buffer);
   
    //关闭套接字
    close(sock);

    return 0;
}

