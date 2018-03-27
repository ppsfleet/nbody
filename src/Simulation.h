#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <iostream>
#include <vector>
#include <tuple>

#include "Particle.h"
#include "Socket.h"

template <class T>
class Simulation {
  public:
    Simulation();
    virtual ~Simulation();
    void run(int iteration);
    virtual void step(double deltaT) = 0;
  protected:
    std::vector<T*> m_particles;
    Socket* m_socket;
};

template <class T>
Simulation<T>::Simulation() {
  Particle* p;
  m_socket = new Socket("172.17.4.25" ,3001);
  //m_socket = new Socket("163.172.21.76" ,8081);
  while (!std::cin.eof()) {
    p = new Particle();
    if(std::cin >> *p) {
      this->m_particles.push_back(p);
      std::cout << *p << std::endl;

    } else {
      delete p;
    }
  }
  m_socket->sendInit(m_particles.size(), 0.01);
  // m_socket->sendInt(m_particles.size());
  //
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
    step(0.01);
  }
}


#endif
