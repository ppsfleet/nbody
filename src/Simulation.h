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
    void run(int iteration);
    virtual void step(double deltaT) = 0;
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

template <class T>
void Simulation<T>::run(int iteration) {
  for (int step_i = 0; step_i < iteration; step_i++) {
    step(0.01);
  }
}


#endif
