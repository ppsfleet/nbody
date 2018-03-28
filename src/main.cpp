#include "BruteForceSimulation.h"
#include "BarnesHutSimulation.h"
#include "Octree.h"
#include <string>
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;
int main(int argc, char *argv[])
{

  // Default
  int opt;
  int nbIter = 500;
  double intervIter = 0.01;
  char* ip = "127.0.0.1";
  int port = 3001;
  string algo = "bruteforce";

  // parse argument
  const char *optString = ":a:n:i:?:p:s:";
  while ((opt = getopt(argc,argv,optString)) != EOF)
  switch(opt)
  {
      case 'a': algo = optarg ; break;
      case 'n': nbIter = atoi(optarg); break;
      case 'i': intervIter = atof(optarg); break;
      case 's': ip = optarg ; break;
      case 'p': port = atoi(optarg) ; break;
      case '?':
      default:
          cerr << "usuage is \n -a <value>: for determining used algorithm, [barneshut, bruteforce] default :  bruteforce" << endl
          << " -n <value>: for setting the number of iteration, default : 500" << endl
          << " -i <value>: for setting the time between each iteration, default : 0.01" << endl
          << " -s <value>: for setting the ip of the server, default : 127.0.0.1" << endl
          << " -p <value>: for setting the port of the server, default : 3001" << endl;
          exit(0);

  }
  // treatment
  if(algo == "barneshut"){
    BarnesHutSimulation simulation;
    simulation.init(ip, port, intervIter);
    simulation.run(nbIter);
  }
  else if(algo == "bruteforce"){
    BruteForceSimulation simulation;
    simulation.init(ip, port, intervIter);
    simulation.run(nbIter);
  }else{
    std::cerr << "Unknown algorithm, try bruteforce or barneshut"<<endl;
  }
}
