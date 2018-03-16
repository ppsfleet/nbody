#ifndef _BARNES_HUT_SIMULATION_H_
#define _BARNES_HUT_SIMULATION_H_

#include <algorithm>

#include "Simulation.h"
#include "Octree.h"

class BarnesHutSimulation: public Simulation<Particle> {
  public:
    void step (double deltaT);
    void computeBoundingBox(double min[3], double max[3]);
    void initTree(double min[3], double max[3]);
    void computeForce(Particle* p, Octree* o);
  private:
    Octree* m_tree = 0;
    double m_thresold = 0;
};

#endif
