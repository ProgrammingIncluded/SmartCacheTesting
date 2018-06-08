#include "tcp_client.hpp"

int main(int argc, char* argv[]){
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd==-1){
    std::cout<<"Failed to open socket"<<std::endl;
    exit(-1);}

  // Bind to loopback address port 0
  struct sockaddr_in local_addr;
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  local_addr.sin_port = 0;
  if(bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr))==-1)
  {
    std::cout<<"Failed to bind to local port"<<std::endl;
    close(sockfd);
    exit(-1);
  }

  // Communicate to loopback address port 20000
  struct sockaddr_in remote_addr;
  remote_addr.sin_family = AF_INET;
  remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  remote_addr.sin_port = 20000;

  if(connect(sockfd, (struct sockaddr*)&remote_addr, sizeof(remote_addr))==-1)
  {
    std::cout<<"Connection failed"<<std::endl;
    close(sockfd);
    exit(-1);
  }


  // // Send a message to the server
  // char *msg = "ping";
  // int msglen = strlen(msg);
  // char *buf = "reply";
  // int buflen = strlen(buf);
  // auto rtt_start = std::chrono::high_resolution_clock::now();
  // send(sockfd, msg, msglen, 0);
  // //Recieve the reply from the server
  // recv(sockfd, (void*)buf, buflen, 0);
  // auto rtt_end = std::chrono::high_resolution_clock::now();
  //
  // std::chrono::duration<double> rtt = rtt_end-rtt_start;
  // std::cout<<"Round trip time is "<<rtt.count()<<std::endl;

  char *msg = (char*)malloc(1024);
  int msglen = 1024;
  std::cout<<"Length of message to send is "<<msglen<<" bytes"<<std::endl;
  int bytes_sent;
  char buf[16] = "asdfg";
  int buflen = strlen(buf);
  int bytes_recv;
  // auto rtt_start = std::chrono::high_resolution_clock::now();
  bytes_sent = send(sockfd, msg, msglen, 0);
  //Recieve the reply from the server
  bytes_recv = recv(sockfd, (void*)buf, buflen, 0);


  if(bytes_sent==-1)
    std::cout<<"Send failed!!!"<<std::endl;
  else
    std::cout<<"Sent "<<bytes_sent<<" bytes to server"<<std::endl;


  if(bytes_recv==-1){
    std::cout<<"Recieve failed!!!"<<std::endl;
    printf("recv:%s (%d)\n",strerror(errno),errno);
  }
  else{
    std::cout<<"Recieved "<<bytes_recv<<" bytes from server"<<std::endl;
    std::cout<<"Recieved:"<<buf<<std::endl;
  }

  auto rtt_start = std::chrono::high_resolution_clock::now();
  close(sockfd);
  auto rtt_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> rtt = rtt_end-rtt_start;
  std::cout<<"Teardown overhead is "<<rtt.count()*1000000<<"us"<<std::endl;


}
