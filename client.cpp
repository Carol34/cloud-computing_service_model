
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>//close()
#include<netinet/in.h>//struct sockaddr_in
#include<arpa/inet.h>//inet_ntoa

#define DEST_PORT 25302
#define DEST_IP_ADDRESS "127.0.0.1"


/*Server side*/
void process_info(int s, char *a[], int count)
{
  float function = 0;
  float value = 0;
  int send_num;
  int recv_num;
  float send_buf[2];
  float recv_buf[2];	 
  if (!strcmp(a[1], "DIV")){
    function = 1;	  
    value = atof(a[2]);	   
  }	 
  else if (!strcmp(a[1], "LOG")){
    function = 2;
    value = atof(a[2]);
  }
  else{
    printf("input error!");
    return;
  }
  //printf("%f\n",function);
  //printf("%f\n",value);
  send_buf[0] = function;
  send_buf[1] = value;
  //printf("begin send\n");
  send_num = send(s,send_buf,sizeof(send_buf),0);
  if (send_num < 0){
    perror("send");
    exit(1);
  }
  else{
    if(function == 1){
      printf("The client sent <%f> and DIV to AWS.\n", send_buf[1]);
    }
    else if(function == 2){
      printf("The client sent <%f> and LOG to AWS.\n", send_buf[1]);
    } 
  }	 
  //printf("begin recv:\n");
  recv_num = recv(s,recv_buf,sizeof(recv_buf),0);
  if(recv_num < 0){
    perror("recv");
    exit(1);
  }
  else {
    if(function == 1){
      printf("According to AWS DIV on <%f> : <%f>.\n", value, recv_buf[0]);
    }
    else if(function == 2){
      printf("According to AWS LOG on <%f> : <%f>.\n", value, recv_buf[0]);
    } 
  }
}

int main(int argc,char *argv[])
{
  printf("The client is up and running.\n");  
  int sock_fd;
  int function = 0;
  char *a[argc] = {0};
  int count = 0;
  float value = 0;
  for (count = 0; count<= argc; count++){
    a[count] = argv[count];
  }
  //--reused from this link: http://blog.csdn.net/tigerjibo/article/details/6775534
  struct sockaddr_in addr_serv;//server address
  sock_fd = socket(AF_INET,SOCK_STREAM,0);
  if(sock_fd < 0){
    perror("sock");
    exit(1);
  }
  else{
    //printf("sock sucessful:\n");
  }
  memset(&addr_serv,0,sizeof(addr_serv));
  addr_serv.sin_family = AF_INET;
  addr_serv.sin_port =  htons(DEST_PORT);
  addr_serv.sin_addr.s_addr = inet_addr(DEST_IP_ADDRESS);
  if( connect(sock_fd,(struct sockaddr *)&addr_serv,sizeof(struct sockaddr)) < 0){
    perror("connect");
    printf("connect (%d)\n",errno);
    exit(1);
  }
  else{
    //printf("connect sucessful\n");
  }
  //--
  process_info(sock_fd, a, count); 
  close(sock_fd);
 }

