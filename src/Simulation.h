#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <iostream>
#include <vector>
#include <string>

#include "Particle.h"
#include "Socket.h"

template <class T>
class Simulation {
  public:
    Simulation();
    virtual ~Simulation();
    void run(int iteration);
    void init(char* datip, int datport, double interv,  bool output, int sendInterval);
    virtual void step(double deltaT) = 0;
    char* ip = "127.0.0.1";
    int port = 3001;
    double intervIter = 0.01;
  protected:
    std::vector<T*> m_particles;
    Socket* m_socket;
};

template <class T>
Simulation<T>::Simulation(){
  Particle* p;

  while (!std::cin.eof()) {
    p = new Particle();
    if(std::cin >> *p) {
      this->m_particles.push_back(p);
      //std::cout << *p << std::endl;

    } else {
      delete p;
    }
  }

}

template <class T>
void Simulation<T>::init(char* datip, int datport, double interv, bool output, int sendInterval) {
  ip = datip;
  port = datport;
  intervIter = interv;
  m_socket = new Socket(ip, port, output, sendInterval);
  m_socket->sendInit(m_particles.size(), intervIter);
}

template <class T>
Simulation<T>::~Simulation() {
  for (auto p: this->m_particles) {
    delete p;
  }
  m_socket->close();
}

template <class T>
void Simulation<T>::run(int iteration) {
  for (int step_i = 0; step_i < iteration; step_i++) {
    step(intervIter);
  }
}


#endif
