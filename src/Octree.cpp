#include "Octree.h"

Octree::Octree(double rx, double ry, double rz, double size):
  m_rx(rx), m_ry(ry), m_rz(rz), m_size(size), m_octants(), m_particle(), m_isLeaf(true), m_id(counter) {
    counter++;
  }

Octree::~Octree() {
  for(auto octant: m_octants) {
    delete octant;
  }
}

double Octree::getMass() {
  return m_mass;
}

void Octree::getPos(double pos[3]) {
  pos[0] = m_mx;
  pos[1] = m_my;
  pos[2] = m_mz;
}

Octree* Octree::getOctant(Particle* p) {
  unsigned char x, y, z, index;
  x = p->getX() > m_rx;
  y = p->getY() > m_ry;
  z = p->getZ() > m_rz;
  index = x | (y << 1) | (z << 2);

  if (!m_octants[index]) {
    double newSize = m_size / 2;

    m_octants[index] = new Octree(
      m_rx + (2 * x - 1) * newSize / 2,
      m_ry + (2 * y - 1) * newSize / 2,
      m_rz + (2 * z - 1) * newSize / 2,
      newSize
    );
  }
  //std::cout << m_id << " Got " << m_quads[index]->m_id << " at " << (int)index << std::endl;
  return m_octants[index];
}

void Octree::insert(Particle* p) {
  //std::cout << "NODE " << m_id << " " <<  m_rx << " " << m_ry  << " " << m_rz << " | " << m_width << " " << m_height << " " << m_depth << std::endl ;
  if (m_isLeaf && !m_particle) {
    //std::cout << m_id << " New leaf " << *p << std::endl;
    m_particle = p;
    m_particle->getPos(m_mx, m_my, m_mz);
    m_mass = m_particle->getMass();

    return;
  }
  Octree* oct;

  if (m_isLeaf && m_particle) {
    //std::cout << m_id << " Changed from leaf to node " << *m_particle << std::endl;
    oct = getOctant(m_particle);
    oct->insert(m_particle);
    m_particle = nullptr;
    m_isLeaf = false;
  }

  //std::cout << m_id << " Inserting new particle in node " << *p << std::endl;
  oct = getOctant(p);
  oct->insert(p);

  updateCenterOfMass();
}

void Octree::updateCenterOfMass() {
  m_mass = m_mx = m_my = m_mz = 0;
  for (int i = 0; i < 8; i++) {
    if (m_octants[i]) {
      m_mx += m_octants[i]->m_mx * m_octants[i]->m_mass;
      m_my += m_octants[i]->m_my * m_octants[i]->m_mass;
      m_mz += m_octants[i]->m_mz * m_octants[i]->m_mass;

      m_mass += m_octants[i]->m_mass;
    }
  }
  m_mx /= m_mass;
  m_my /= m_mass;
  m_mz /= m_mass;
}

std::ostream& operator<<(std::ostream& out, Octree& tree) {
  return tree.print(out, 0);
}

std::ostream& Octree::print(std::ostream& out, int level) {
  if (m_particle) {
    out << "Particle " << *m_particle << std::endl;
  } else {
    out << "Node Bounding Box: (x, y, z) = (" <<
      m_rx << ", " << m_ry << ", " << m_rz <<
      ") size = " << m_size <<
      "; Center of mass: (x, y, z) = (" <<
      m_mx << ", " << m_my << ", " << m_mz << ") " <<
      "mass = " << m_mass << std::endl;

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j <= level; j++)
        out << "  ";
      out << i  << ": ";
      if (m_octants[i]) {
        m_octants[i]->print(out, level+1);
      } else {
        out << std::endl;
      }
    }
  }
  return out;
}

int Octree::counter = 0;
