//client1.cpp

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

main(int argc, char *argv[]){
  int function = 0;
  char *a[argc]={0};
  int count = 0;
  float value = 0;
  //store function and input
  for (count = 0; count<=argc; count++){
    a[count] = argv[count]; 
  }
  //go to corresponding function
  if (argc == 3){
    if (!strcmp(a[1], "DIV")){
	  function = 1;
	  printf("%d\n",function);
	  value = atof(a[2]); 
	  printf("%f\n",value);
	  float b[2] = {0};
	  b[0] = function;
	  b[1] = value;
	    //创建套接字
	    int sock = socket(AF_INET, SOCK_STREAM, 0);

	    //向服务器（特定的IP和端口）发起请求
	    struct sockaddr_in serv_addr;
	    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
	    serv_addr.sin_family = AF_INET;  //使用IPv4地址
	    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	    serv_addr.sin_port = htons(25302);  //端口
	    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	   
	    //读取服务器传回的数据
	    //write(serv_sock, function, sizeof(function);
	    //write(serv_sock, value, sizeof(value));
	    char bufferS[5]={0};
	    bufferS[0] = b[0];
	    bufferS[1] = b[1];
	    write(sock, bufferS, sizeof(bufferS));
	    char bufferR[5]={0};
	    read(sock, bufferR, 5);
	     
	    printf("Message form server: %d\n", bufferR[0]);
	  
	}
    else if (!strcmp(a[1], "LOG")){
	  function = 2;
	  printf("%d\n",function);
	  value = atof(a[2]); 
	  printf("%f\n",value);	
	  float b[2] = {0};
	  b[0] = function;
	  b[1] = value;
	    //创建套接字
	    int sock = socket(AF_INET, SOCK_STREAM, 0);

	    //向服务器（特定的IP和端口）发起请求
	    struct sockaddr_in serv_addr;
	    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
	    serv_addr.sin_family = AF_INET;  //使用IPv4地址
	    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	    serv_addr.sin_port = htons(25302);  //端口
	    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	   
	    //send
	    //write(serv_sock, function, sizeof(function);
	    //write(serv_sock, value, sizeof(value));
	    char bufferS[5]={0};
	    bufferS[0] = b[0];
	    bufferS[1] = b[1];
	    write(sock, bufferS, sizeof(bufferS));
	    char bufferR[5]={0};
	    read(sock, bufferR, 5);
	   
	    printf("Message form server: %d\n", bufferR[0]);
	   
       	}
    else {
          //error
	  printf("input error!");
	  return 0;
      }
   }
  else
    return 0;
}
