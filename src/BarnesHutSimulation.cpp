#include "BarnesHutSimulation.h"

void BarnesHutSimulation::run () {
  double min[3], max[3];

  computeBoundingBox(min, max);
  initTree(min, max);
  std::cout << *m_tree;
}

void BarnesHutSimulation::computeBoundingBox(double min[3], double max[3]) {
  for (int dim = 0; dim < 3; dim++) {
    min[dim] = m_particles[0]->getPos(dim);
    max[dim] = m_particles[0]->getPos(dim);
  }

  for (unsigned int i = 1; i < m_particles.size(); i++) {
    for (int dim = 0; dim < 3; dim++) {
      if (m_particles[i]->getPos(dim) < min[dim])
        min[dim] = m_particles[i]->getPos(dim);
      if (m_particles[i]->getPos(dim) > max[dim])
        max[dim] = m_particles[i]->getPos(dim);
    }
  }
}

void BarnesHutSimulation::initTree(double min[3], double max[3]) {
  if (m_tree) {
    delete m_tree;
  }

  m_tree = new Octree(
    (min[0] + max[0])/2,
    (min[1] + max[1])/2,
    (min[2] + max[2])/2,
    std::max(std::max(max[0] - min[0], max[1] - min[1]), max[2] - min[2])
  );

  for (auto p: m_particles) {
    m_tree->insert(p);
  }
}
