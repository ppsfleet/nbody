#ifndef _IPARTICLES_H_
#define _IPARTICLES_H_

#include <cmath>

#define G 1 //6.67408e-11

class IParticle {
  public:
    virtual void getPos(double pos[3]) = 0;
    virtual double getMass() = 0;
    static void computeForce(IParticle* p1, IParticle* p2, double force[3]);
};

#endif
