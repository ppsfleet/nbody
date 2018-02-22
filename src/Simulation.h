#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <iostream>
#include <vector>

#include "Particle.h"

template <class T>
class Simulation {
  public:
    Simulation();
    virtual ~Simulation();
    virtual void run() = 0;
  protected:
    std::vector<T*> m_particles;
};

template <class T>
Simulation<T>::Simulation() {
  Particle* p;

  while (!std::cin.eof()) {
    p = new Particle();
    if(std::cin >> *p) {
      this->m_particles.push_back(p);
      std::cout << *p << std::endl;
    } else {
      delete p;
    }
  }

}

template <class T>
Simulation<T>::~Simulation() {
  for (auto p: this->m_particles) {
    delete p;
  }
}

#endif
