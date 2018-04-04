# Nbody simulation

To execute the project run `make` and then the binary should be in the `/bin` folder. During the compilation the following folder will be created :
 - `bin/` : contains the program binary ;
 - `build/` : contains the object (`*.o`) and the dependency (`*.d`) files.
 The sources are in the `src` folder and the datasets are stored in the `datasets` folder.


The parameters of the program are the following 
 - `-a <value>`: for determining used algorithm, [barneshut, bruteforce] default :  bruteforce
 - `-n <value>`: for setting the number of iteration, default : 500
 - `-i <value>`: for setting the time between each iteration, default : 0.01
 - `-s <value>`: for setting the ip of the server, default : 127.0.0.1
 - `-p <value>`: for setting the port of the server, default : 3001
 - `-t <value>`: for setting the threshold of barneshut, default : 0.5
 - `-o : for setting the output method, default : socket
 - `-u <value>`: for setting the interval between each output of particle (for exemple, 3 : for 1 particle out of 3), default : 1 (all particles outputed). A value of 0 disable the output of the result, useful for benchark.
