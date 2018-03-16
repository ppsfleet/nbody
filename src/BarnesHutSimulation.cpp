#include "BarnesHutSimulation.h"

void BarnesHutSimulation::step (double deltaT) {
  double min[3], max[3];

  computeBoundingBox(min, max);
  initTree(min, max);
  for (auto p: m_particles) {
    p->setForce(0, 0, 0);
  }
  for (auto p: m_particles) {
    //std::cerr << p->m_id << " ";
    computeForce(p, m_tree);
    //std::cerr << std::endl;
  }
  for (auto p: m_particles) {
    p->update(deltaT);
    std::cout << *p << std::endl;
  }
}

void BarnesHutSimulation::computeForce(Particle* p, Octree* o) {
  if (o->getParticle() == p)
    return;
  if (o->isLeaf() /*|| o->getSDQuotient(p) < m_thresold*/) {
    double force[3];
    IParticle::computeForce(p, o->getParticle(), force);
    p->addForce(force[0], force[1], force[2]);
    //std::cerr << o->getParticle()->m_id << ", ";
  } else {
    for (int i = 0; i < 8; i++) {
      if (o->getOctant(i))
        computeForce(p, o->getOctant(i));
    }
  }
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
