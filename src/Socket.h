#ifndef _SOCKET_H_
#define _SOCKET_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "Particle.h"
#include <netdb.h>

class Socket {
  public:
    Socket (char* ip, int port);
    void sendParticle (Particle *p);
    void sendInt (int arg);
    void sendDouble (double arg);
    double* receive ();
    void close();
  private:
    int sockfd, portno;
    double buffer[3];
};

#endif
