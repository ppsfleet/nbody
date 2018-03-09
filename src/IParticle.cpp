#include "IParticle.h"

void IParticle::computeForce(IParticle* p1, IParticle* p2, double force[3]) {
  double posP1[3], posP2[3], deltaPos[3];
  double r2(0), r, valForce;

  p1->getPos(posP1);
  p2->getPos(posP2);
  for (int i = 0; i < 3; i++) {
    deltaPos[i] = posP2[i] - posP1[i];
    r2 += deltaPos[i] * deltaPos[i];
  }

  r = sqrt(r2);
  valForce = G*p1->getMass()*p2->getMass()/r2;

  for (int i = 0; i < 3; i++) {
    force[i] = valForce * deltaPos[i] / r;
  }
}
