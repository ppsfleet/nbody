#include "Particle.h"

Particle::Particle(double mass, double vx, double vy, double vz, double rx, double ry, double rz):
  m_mass(mass),
  m_vx(vx),
  m_vy(vy),
  m_vz(vz),
  m_rx(rx),
  m_ry(ry),
  m_rz(rz)
{
  this->m_id = Particle::counter++;
}

Particle::Particle(): Particle(0, 0, 0, 0, 0, 0, 0) {}

Particle::~Particle() {}

double Particle::getX() {
  return this->m_rx;
}

double Particle::getY() {
  return this->m_ry;
}

double Particle::getZ() {
  return this->m_rz;
}

double Particle::getMass() {
  return this->m_mass;
}

void Particle::setForce(double fx, double fy, double fz) {
  this->m_fx = fx;
  this->m_fy = fy;
  this->m_fz = fz;
}

void Particle::addForce(double fx, double fy, double fz) {
  this->m_fx += fx;
  this->m_fy += fy;
  this->m_fz += fz;
}

void Particle::update(double deltaT) {
  this->m_vx += deltaT * this->m_fx / this->m_mass;
  this->m_vy += deltaT * this->m_fy / this->m_mass;
  this->m_vz += deltaT * this->m_fz / this->m_mass;

  this->m_rx += deltaT * this->m_vx;
  this->m_ry += deltaT * this->m_vy;
  this->m_rz += deltaT * this->m_vz;
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
    p.m_rx << " " << p.m_ry << " " << p.m_rz << " " <<
    p.m_fx << " " << p.m_fy << " " << p.m_fz << " " <<
    p.m_vx << " " << p.m_vy << " " << p.m_vz;
}

std::istream& operator>>(std::istream& in, Particle& p) {
  return in >> p.m_mass >> p.m_rx >> p.m_ry >> p.m_rz >> p.m_vx >> p.m_vy >> p.m_vz;
}

int Particle::counter = 0;
