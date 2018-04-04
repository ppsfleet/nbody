#include <omp.h>

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

void Particle::resetForce() {
  m_vforces.clear();
}

void Particle::setForce(double fx, double fy, double fz) {
  std::array<double, 3> force;
  force[0] = fx;
  force[1] = fy;
  force[2] = fz;

  m_vforces.push_back(force);
}

void Particle::addForce(double fx, double fy, double fz) {
  int tid = omp_get_thread_num();
  m_vforces[tid][0] += fx;
  m_vforces[tid][1] += fy;
  m_vforces[tid][2] += fz;
}

double* Particle::getForce() {
  return m_force;
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
}

void Particle::reduceForces() {
  m_force[0] = 0;
  m_force[1] = 0;
  m_force[2] = 0;


  for (auto vforce: m_vforces) {
    m_force[0] += vforce[0];
    m_force[1] += vforce[1];
    m_force[2] += vforce[2];
  }
}

Particle* Particle::plus(Particle * first, Particle * second) {
  double *second_force = second->getForce();
  first->addForce(second_force[0], second_force[1], second_force[2]);
  return first;
}

Particle& Particle::operator+=(Particle & other) {
  double *other_force = other.getForce();
  //std::cout << this->m_force[0] << " coco ";
  this->addForce(other_force[0], other_force[1], other_force[2]);
  //std::cout << this->m_force[0] << std::endl;
  return *this;
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
