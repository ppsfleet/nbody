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

void Particle::computeForce(Particle* p1, Particle* p2, double& fx, double& fy, double& fz) {
  double dx = p2->getX() - p1->getX();
  double dy = p2->getY() - p1->getY();
  double dz = p2->getZ() - p1->getZ();

  double r = sqrt(dx*dx + dy*dy + dz*dz);
  double force = G*p1->getMass()*p2->getMass()/(r*r);
  fx = force * dx / r;
  fy = force * dy / r;
  fz = force * dz / r;
}

void Particle::computeForce(Particle* p1, Particle* p2) {
  double fx, fy, fz;
  Particle::computeForce(p1, p2, fx, fy, fz);
  p1->addForce(fx, fy, fz);
  p2->addForce(-fx, -fy, -fz);
}

std::ostream& operator<<(std::ostream& out, const Particle& p) {
  return out << p.m_id << " " <<
    p.m_position[0] << " " << p.m_position[1] << " " << p.m_position[2] << " " <<
    p.m_force[0] << " " << p.m_force[1] << " " << p.m_force[2] << " " <<
    p.m_velocity[0] << " " << p.m_velocity[1] << " " << p.m_velocity[2];
}

std::istream& operator>>(std::istream& in, Particle& p) {
  return in >> p.m_mass >>
    p.m_position[0] >> p.m_position[1] >> p.m_position[2] >>
    p.m_velocity[0] >> p.m_velocity[1] >> p.m_velocity[2];
}

int Particle::counter = 0;
