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
         p->setForce(0, 0, 0);
       }
       for (unsigned int i = 0; i < m_particles.size(); i++) {
         //std::cerr << m_particles[i]->m_id << " ";
         #pragma omp parallel for
         for (unsigned int j = 0; j < m_particles.size(); j++) {
           if (i != j) {
             //std::cerr << m_particles[j]->m_id << ", ";
             //Particle::computeForce(m_particles[i], m_particles[j]);
             double force[3];
             IParticle::computeForce(m_particles[i], m_particles[j], force);
             m_particles[i]->addForce(force[0], force[1], force[2]);
           }
         }
         //std::cerr << std::endl;
         //m_particles[i]->update(deltaT);
         //std::cout << *m_particles[i] << std::endl;
       }
       for (auto p: m_particles) {
         p->update(deltaT);
         //std::cout << *p << std::endl;
         m_socket->sendParticle(p);
       }
     }
 };

#endif
