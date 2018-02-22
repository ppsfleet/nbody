#ifndef _BARNES_HUT_SIMULATION_H_
#define _BARNES_HUT_SIMULATION_H_

#include "Simulation.h"
#include "Octree.h"

class BarnesHutSimulation: public Simulation<Particle> {
  public:
    void run () {
      double minX, maxX, minY, maxY, minZ, maxZ;
      minX = maxX = m_particles[0]->getX();
      minY = maxY = m_particles[0]->getY();
      minZ = maxZ = m_particles[0]->getZ();

      for (unsigned int i = 1; i < m_particles.size(); i++) {
        if (m_particles[i]->getX() < minX)
          minX = m_particles[i]->getX();
        if (m_particles[i]->getX() > maxX)
          maxX = m_particles[i]->getX();
        if (m_particles[i]->getY() < minY)
          minY = m_particles[i]->getY();
        if (m_particles[i]->getY() > maxY)
          maxY = m_particles[i]->getY();
        if (m_particles[i]->getZ() < minZ)
          minZ = m_particles[i]->getZ();
        if (m_particles[i]->getZ() > maxZ)
          maxZ = m_particles[i]->getZ();
      }
      Octree tree(
        (minX + maxX)/2,
        (minY + maxY)/2,
        (minZ + maxZ)/2,
        maxX - minX,
        maxY - minY,
        maxZ - minZ
      ) ;
      for (auto p: m_particles) {
        tree.insert(p);
      }
      std::cout << tree;
    }
};

#endif
