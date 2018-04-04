#include "Particle.h"

Particle::Particle(double mass, double vx, double vy, double vz, double rx, double ry, double rz):
  m_mass(mass),
  m_velocity(),
  m_force()
{
  m_id = Particle::counter++;
  m_position[0] = rx;
  m_position[1] = ry;
  m_position[2] = rz;
}

Particle::Particle(): Particle(0, 0, 0, 0, 0, 0, 0) {}

Particle::~Particle() {}

double Particle::getX() {
  return m_position[0];
}

double Particle::getY() {
  return m_position[1];
}

double Particle::getZ() {
  return m_position[2];
}

double Particle::getPos(int dim) {
  return m_position[dim];
}

void Particle::getPos(double pos[3]) {
  for (int i = 0; i < 3; i++) {
    pos[i] = m_position[i];
  }
}

void Particle::getPos(double& rx, double& ry, double& rz) {
  rx = m_position[0];
  ry = m_position[1];
  rz = m_position[2];
}

double Particle::getMass() {
  return m_mass;
}

void Particle::setForce(double fx, double fy, double fz) {
  m_force[0] = fx;
  m_force[1] = fy;
  m_force[2] = fz;
}

void Particle::addForce(double fx, double fy, double fz) {
  m_force[0] += fx;
  m_force[1] += fy;
  m_force[2] += fz;
}

void Particle::update(double deltaT) {
  for (int i = 0; i < 3; i++) {
    m_velocity[i] += deltaT * m_force[i] / m_mass;
    m_position[i] += deltaT * m_velocity[i];
  }
}

void Particle::computeForce(Particle* p1, Particle* p2) {
  double force[3];
  IParticle::computeForce(p1, p2, force);

  p1->addForce(force[0], force[1], force[2]);
  p2->addForce(-force[0], -force[1], -force[2]);
}

std::ostream& operator<<(std::ostream& out, const Particle& p) {
  std::cout.precision(17);
  return out <<
    //p.m_force[0] << " " << p.m_force[1] << " " << p.m_force[2] << " " <<
    std::fixed << p.m_position[0] << " " << std::fixed << p.m_position[1] << " " << std::fixed << p.m_position[2];
}

std::istream& operator>>(std::istream& in, Particle& p) {
  return in >> p.m_mass >>
    p.m_position[0] >> p.m_position[1] >> p.m_position[2] >>
    p.m_velocity[0] >> p.m_velocity[1] >> p.m_velocity[2];
}

int Particle::counter = 0;
