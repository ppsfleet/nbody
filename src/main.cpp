#include "BruteForceSimulation.h"
#include "BarnesHutSimulation.h"
#include "Octree.h"

int main(int argc, const char *argv[])
{

  BruteForceSimulation simulation;
  simulation.run(2500);
  /*
  BarnesHutSimulation simulation;
  simulation.run(1);
  /*
  Octree tree(0., 0., 0., 2., 2., 2.);
  Particle p(1., 0., 0., 0., -.5, .5, -.5);
  Particle p2(1., 0., 0., 0., -.5, -.5, -.5);
  Particle p3(1., 0., 0., 0., -.5, -.4, -.5);
  tree.insert(&p);
  tree.insert(&p2);
  tree.insert(&p3);
  std::cout << tree;*/
}
