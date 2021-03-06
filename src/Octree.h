#ifndef _OCTREE_H_
#define _OCTREE_H_

#include <iostream>

#include "Particle.h"
#include "IParticle.h"

class Octree: public IParticle {
  public:
    Octree(double rx, double ry, double rz, double size);
    virtual ~Octree();
    void insert(Particle* p);
    Octree* getOctant(Particle* p);
    Octree* getOctant(int index);
    double getMass();
    void getPos(double pos[3]);
    bool isLeaf();
    Particle* getParticle();
    double getSDQuotient(Particle* p);

    static int counter;

    friend std::ostream& operator<<(std::ostream& out, Octree& tree);
  private:
    double m_rx;
    double m_ry;
    double m_rz;

    double m_size;

    double m_mass = 0;

    // Center of mass
    double m_mx = 0;
    double m_my = 0;
    double m_mz = 0;

    /* Indices :
     *
     * Back (z <= m_rz)
     *         2 | 3
     *      -----------
     *         0 | 1
     *
     * Front (z > m_rz)
     *         6 | 7   y > m_ry
     *      -----------
     *         4 | 5   y <= m_ry
     * x <= m_rx | x > m_rx
     */
    Octree* m_octants[8];

    Particle* m_particle;
    bool m_isLeaf;
    int m_id;

    std::ostream& print(std::ostream& out, int level);
    void updateCenterOfMass();
};

#endif
