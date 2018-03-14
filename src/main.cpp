#include "BruteForceSimulation.h"
#include "BarnesHutSimulation.h"
#include "Octree.h"
#include <string>
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[])
{

  // Default
  int opt;
  int nbIter = 500;
  float intervIter = 1;
  string algo = "bruteforce";

  // parse argument
  const char *optString = /*n*/":a:n:i:?";
  while ((opt = getopt(argc,argv,optString)) != EOF)
  switch(opt)
  {
      case 'a': algo = optarg ; break;
      case 'n': nbIter = boost::lexical_cast<int>(optarg); break;
      case 'i': intervIter = boost::lexical_cast<float>(optarg); break;
      case '?': fprintf(stderr, "usuage is \n -a <value>: for determining used algorithm, [barneshut, bruteforce] default :  bruteforce \n"
        " -n <value>: for setting the number of iteration, default : 500\n"
        " -i <value>: for setting the time between each iteration, default : 1\n ");
      default: cout<<endl; abort();
  }

  // treatment
  cout << "algo " << algo << " nb itération " << nbIter << " tps Interval " << intervIter << endl;
  if(algo == "barneshut"){
    BarnesHutSimulation simulation;
    simulation.run(nbIter);//, intervIter);
  }
  else if(algo == "bruteforce"){
    BruteForceSimulation simulation;
    simulation.run(nbIter);//, intervIter);
  }else{
    std::cerr <<"Unknown algorithm, try bruteforce or barneshut"<<endl;
  }

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
