#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <iostream>
#include <cmath>

#define G 1 //6.67408e-11

class Particle {
  public:
    Particle(double mass, double vx, double vy, double vz, double rx, double ry, double rz);
    Particle();
    virtual ~Particle();

    double getX();
    double getY();
    double getZ();
    double getPos(int dim);
    void getPos(double& rx, double& ry, double& rz);

    double getMass();

    void setForce(double fx, double fy, double fz);
    void addForce(double fx, double fy, double fz);
    void update(double deltaT);

    static void computeForce(Particle* p1, Particle* p2, double& fx, double& fy, double& fz);
    static void computeForce(Particle* p1, Particle* p2);

    friend std::ostream& operator<<(std::ostream& out, const Particle& p);
    friend std::istream& operator>>(std::istream& in, Particle& p);

    static int counter;
  private:
    double m_mass;

    double m_velocity[3];

    double m_position[3];

    double m_force[3];

    int m_id;
};

#endif
