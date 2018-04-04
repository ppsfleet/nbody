#ifndef _BRUTE_FORCE_SIMULATION_H_
#define _BRUTE_FORCE_SIMULATION_H_

#include "Simulation.h"
#include <unistd.h>
#include <algorithm>
#include <omp.h>

/*
 * Brute force simulation.
 * Complexity = n(n+1)/2 + n = O(n^2)
 */

#pragma omp declare reduction(ParticleForceAdd: std::vector<Particle*>: \
                              std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), Particle::plus)) \
                    initializer(omp_priv = omp_orig)
                    //omp_out += omp_in)

class BruteForceSimulation: public Simulation<Particle> {
  public:
    void step (double deltaT) {

      for (auto p: m_particles) {
        p->resetForce();
        for (int i = 0; i < omp_get_num_threads(); i++) {
          p->setForce(0.0, 0.0, 0.0);
        }
      }

      //std::cout << "plpl" << std::endl;

      omp_set_num_threads(4);
      #pragma omp parallel for //schedule(static) //reduction(ParticleForceAdd:m_particles)//reduction(+:force)
      for (unsigned int i = 0; i < m_particles.size(); i++) {
        //double force[3] = {0};
        for (unsigned int j = i+1; j < m_particles.size(); j++) {

          //std::cout << omp_get_thread_num() << " toto" << std::endl;
          double force[3];
          IParticle::computeForce(m_particles[i], m_particles[j], force);
          m_particles[i]->addForce(force[0], force[1], force[2]);
          m_particles[j]->addForce(-force[0], -force[1], -force[2]);

          /*
          Particle localParticleI = *m_particles[i];
          localParticleI.setForce(0.0, 0.0, 0.0);
          Particle localParticleJ = *m_particles[j];
          localParticleJ.setForce(0.0, 0.0, 0.0);

          Particle::computeForce(&localParticleI, &localParticleJ);
          //std::cout << i << " uu " << j << std::endl;
          std::cout << m_particles[i]->getForce()[0] << " caca " << m_particles[j]->getForce()[0] << std::endl;
          *m_particles[i] += localParticleI;
          *m_particles[j] += localParticleJ;
          std::cout << m_particles[i]->getForce()[0] << " caca " << m_particles[j]->getForce()[0] << std::endl;

          //int tnb = omp_get_thread_num();
          //std::cout << tnb << " doing " << *m_particles[i] << std::endl;
          //usleep(100000);
          /*if(i != j) {
            double loca_force[3] = {};
            IParticle::computeForce(m_particles[i], m_particles[j], loca_force);

            force[0] += loca_force[0];
            force[1] += loca_force[1];
            force[2] += loca_force[2];

          }*/
          //Particle::computeForce(m_particles[i], m_particles[j]);
        }
        //m_particles[i]->addForce(force[0], force[1], force[2]);
      }


      for (auto p: m_particles) {
        p->reduceForces();
        //std::cout << p->getForce()[0]<< std::endl;
        p->update(deltaT);
        std::cout << *p << std::endl;
      }
    }
};

#endif
