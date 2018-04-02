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
  float threshold = 0.5;
  char* ip = "127.0.0.1";
  int port = 3001;
  string algo = "bruteforce";
  bool output = false;
  int send = 1;
  // parse argument
  const char *optString = ":a:n:i:?:p:s:t:u:o";
  while ((opt = getopt(argc,argv,optString)) != EOF)
  switch(opt)
  {
      case 'a': algo = optarg ; break;
      case 'n': nbIter = atoi(optarg); break;
      case 'i': intervIter = atof(optarg); break;
      case 't': threshold = atof(optarg); break;
      case 'o': output = true; break;
      case 'u': send = atoi(optarg); break;
      case 's': ip = optarg ; break;
      case 'p': port = atoi(optarg) ; break;
      case '?':
      default:
          cerr << "usuage is \n -a <value>: for determining used algorithm, [barneshut, bruteforce] default :  bruteforce" << endl
          << " -n <value>: for setting the number of iteration, default : 500" << endl
          << " -i <value>: for setting the time between each iteration, default : 0.01" << endl
          << " -s <value>: for setting the ip of the server, default : 127.0.0.1" << endl
          << " -p <value>: for setting the port of the server, default : 3001" << endl
          << " -t <value>: for setting the threshold of barneshut, default : 0.5" << endl
          << " -o : for setting the output method, default : socket" << endl
          << " -u <value>: for setting the interval between each output of particle (for exemple, 3 : for 1 particle out of 3), default : 1 (all particles outputed)" << endl;
          exit(0);

  }
  // treatment
  if(algo == "barneshut"){
    BarnesHutSimulation simulation;
    simulation.init(ip, port, intervIter, output, send);
    simulation.run(nbIter);
  }
  else if(algo == "bruteforce"){
    BruteForceSimulation simulation;
    simulation.init(ip, port, intervIter, output, send);
    simulation.run(nbIter);
  }else{
    std::cerr << "Unknown algorithm, try bruteforce or barneshut"<<endl;
  }
}
