#include "tcp_client.hpp"

int main(int argc, char* argv[]){
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd==-1){
    std::cout<<"Failed to open socket"<<std::endl;
    exit(-1);}

  // Bind to loopback address port 20000
  struct sockaddr_in local_addr;
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  local_addr.sin_port = 20000;
  if(bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr))==-1){
    std::cout<<"Failed to bind to local port"<<std::endl;
    close(sockfd);
    exit(-1);
  }

  // Listen for connection from loopback address port 20000
  struct sockaddr_in client_addr;
  client_addr.sin_family = AF_INET;
  client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  client_addr.sin_port = 0;
  listen(sockfd, 1);
  int socklen = sizeof(client_addr);
  socklen_t* client_addrl = (socklen_t*) &socklen;
  int clientfd = accept(sockfd, (struct sockaddr*)&client_addr, client_addrl);
  if(clientfd == -1){
    std::cout<<"Failed to accept connection from client"<<std::endl;
    close(sockfd);
    close(clientfd);
    exit(-1);
  }

  //Setup buffers
  char *buf = (char*)malloc(1024);
  int buflen = 1024;
  char *reply = "reply";
  int replylen = strlen(reply);
  int bytes_recv, bytes_sent;

  //Recieve the data from the server
  bytes_recv = recv(clientfd, (void*)buf, buflen, 0);

  //Send reply back
  bytes_sent = send(clientfd, reply, replylen, 0);

  if(bytes_recv==-1){
    std::cout<<"Recv from client failed"<<std::endl;
    close(sockfd);
    close(clientfd);
    exit(-1);
  }
  else{
    std::cout<<"Recieved "<<bytes_recv<<" bytes from client"<<std::endl;
  }

  if(bytes_sent==-1){
    std::cout<<"Send to client failed"<<std::endl;
    close(sockfd);
    close(clientfd);
    exit(-1);
  }
  else{
    std::cout<<"Sent "<<bytes_sent<<" bytes to client"<<std::endl;
  }
  // close(sockfd);
}
