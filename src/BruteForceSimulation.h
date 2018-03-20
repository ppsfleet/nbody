#ifndef _BRUTE_FORCE_SIMULATION_H_
#define _BRUTE_FORCE_SIMULATION_H_

#include "Simulation.h"

/*
 * Brute force simulation.
 * Complexity = n(n+1)/2 + n = O(n^2)
 */

class BruteForceSimulation: public Simulation<Particle> {
  public:
    void step (double deltaT) {
      for (auto p: m_particles) {
        p->setForce(0.0, 0.0, 0.0);
      }
      for (unsigned int i = 0; i < m_particles.size(); i++) {
        //double force[3] = {0};
        #pragma omp parallel for
        for (unsigned int j = i+1; j < m_particles.size(); j++) {
          /*if(i != j) {
            double loca_force[3] = {};
            IParticle::computeForce(m_particles[i], m_particles[j], loca_force);

            force[0] += loca_force[0];
            force[1] += loca_force[1];
            force[2] += loca_force[2];
            //Particle::computeForce(m_particles[i], m_particles[j]);
          }*/
          Particle::computeForce(m_particles[i], m_particles[j]);
        }
        //m_particles[i]->addForce(force[0], force[1], force[2]);
        m_particles[i]->update(deltaT);
        std::cout << *m_particles[i] << std::endl;
      }
    }
};

#endif
