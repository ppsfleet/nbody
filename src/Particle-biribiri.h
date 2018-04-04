#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "IParticle.h"

#include <iostream>
#include <cmath>
//#include <array>
//#include <vector>

class Particle: public IParticle {
  public:
    Particle(double mass, double vx, double vy, double vz, double rx, double ry, double rz);
    Particle();
    virtual ~Particle();

    double getX();
    double getY();
    double getZ();
    double getPos(int dim);
    void getPos(double pos[3]);
    void getPos(double& rx, double& ry, double& rz);

    double getMass();

    //void resetForce();
    void setForce(double fx, double fy, double fz);
    void addForce(double fx, double fy, double fz);
    //double* getForce();
    void update(double deltaT);

    static void computeForce(Particle* p1, Particle* p2);
    //void reduceForces();

    //static Particle* plus(Particle * first, Particle * second);
    //Particle& operator+=(Particle & other);
    friend std::ostream& operator<<(std::ostream& out, const Particle& p);
    friend std::istream& operator>>(std::istream& in, Particle& p);

    static int counter;
    int m_id;
  private:
    double m_mass;

    double m_velocity[3];

    double m_position[3];

    double m_force[3];
    //std::vector<std::array<double, 3> > m_vforces;

};

#endif
