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
      case '?':
      default:
          cerr << "usuage is \n -a <value>: for determining used algorithm, [barneshut, bruteforce] default :  bruteforce" << endl
          << " -n <value>: for setting the number of iteration, default : 500" << endl
          << " -i <value>: for setting the time between each iteration, default : 1" << endl;
          exit(0);

  }

  // treatment
  cerr << "algo " << algo << " nb itération " << nbIter << " tps Interval " << intervIter << endl;
  if(algo == "barneshut"){
    BarnesHutSimulation simulation;
    simulation.run(nbIter);//, intervIter);
  }
  else if(algo == "bruteforce"){
    BruteForceSimulation simulation;
    simulation.run(nbIter);//, intervIter);
  }else{
    std::cerr << "Unknown algorithm, try bruteforce or barneshut"<<endl;
  }
}
