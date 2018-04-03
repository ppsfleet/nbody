#include "Socket.h"


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

Socket::Socket(char* ip, int port, bool output, int sendInterval)
{
  outputMethod = output;
  sendInter = sendInterval;
  sendInterTmp = sendInter;
  if (!this->outputMethod) {
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
}

void Socket::sendParticle(Particle *p){
  // Disable output for sendInterval == 0
  if (sendInterTmp == 0)
    return;
  if (sendInterTmp > 1){
    sendInterTmp--;
  }else{
    int n;
    p->getPos(buffer);
    if (!this->outputMethod){
      n = write(sockfd,buffer,sizeof(buffer));
      if (n < 0)
           error("ERROR writing to socket");
    }else{
      std::cout << *p << std::endl;
    }
    sendInterTmp = sendInter;
  }
}

void Socket::sendInt(int arg){
  if (!this->outputMethod){
    int n;
    n = write(sockfd,&arg,sizeof(arg));
    if (n < 0)
         error("ERROR writing to socket");
  }else{
   std::cout << arg << std::endl;
  }
}

void Socket::sendDouble(double arg){
  if (!this->outputMethod){
    int n;
    n = write(sockfd,&arg,sizeof(arg));
    if (n < 0)
         error("ERROR writing to socket");
  }else{
    std::cout << arg << std::endl;
  }
}
void Socket::sendInit(int nbParts, double interv){
  int n;
  unsigned char bytes[12];
  int nbPartsOrdered = htonl(nbParts);
  memcpy ( bytes, &nbPartsOrdered, 4 );
  memcpy ( bytes+4, &interv, 8 );
  if (!this->outputMethod){
    n = write(sockfd,bytes,sizeof(bytes));
    if (n < 0)
         error("ERROR writing to socket");
  }else{
    std::cout << nbParts << " " <<interv << std::endl;
  }
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
  if (!this->outputMethod){
    ::close(sockfd);
  }
}
