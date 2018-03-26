#include "Socket.h"


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

Socket::Socket(char* ip, int port)
{

  struct sockaddr_in serv_addr;
  struct hostent *server;

  portno = port;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      error("ERROR opening socket");
  server = gethostbyname(ip);
  if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
       (char *)&serv_addr.sin_addr.s_addr,
       server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
      error("ERROR connecting");

}

void Socket::sendParticle(Particle *p){
  int n;
  p->getPos(buffer);
  n = write(sockfd,buffer,sizeof(buffer));
  if (n < 0)
       error("ERROR writing to socket");
}

void Socket::sendInt(int arg){
  int n;
  n = write(sockfd,&arg,sizeof(arg));
  if (n < 0)
       error("ERROR writing to socket");
}

void Socket::sendDouble(double arg){
  int n;
  n = write(sockfd,&arg,sizeof(arg));
  if (n < 0)
       error("ERROR writing to socket");
}

double* Socket::receive(){
  int n;
  bzero(buffer,12);
  n = read(sockfd,buffer,12);
  if (n < 0)
       error("ERROR reading from socket");
  return buffer;
}

void Socket::close(){
  ::close(sockfd);
}
