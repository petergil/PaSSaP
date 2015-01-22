#ifndef PASSAP_PARTICLE_OPERATIONS_HXX
#define PASSAP_PARTICLE_OPERATIONS_HXX

#include "datatypes.hxx"

/**
  * Calculate collision time between two particles.
  *
  * This is done using equation 3.67 in Allen - Computer
  * Simulation of Liquids. Note the conditions for collision
  * actually occuring.
  *
  * @param a first particle
  * @param b second particle
  *
  * @return Time to collision. TODO: find special value to signify
  * no collision occurs (negative?)
  */
ftype calculate_collision_time(const particle &a, const particle &b);

/**
  * Update position of particle par.
  *
  * fabs(fmod(par.pos.x + par.vel.x * dt, L))
  *
  *
  */
void update_position(particle *par, ftype dt, ftype L);

/**
  * Perform collision between particle a and b.
  *
  * see equation 3.69 in Computer Simulation of Liquids.
  *
  */
void perform_collision(particle *a, particle *b);

/**
  * print particle info to stdout.
  * \todo more pretty-printing
  * \param p particle to print
  *
  */ 
void print_particle(const particle &p);

/**
  * Zap coordinate back into unit cell after overshooting it.
  *
  * \todo  exception on abs(coord) > 2*L (this means that we have exceeded /c/ in this reference frame)
  *
  * \param coord coordinate
  * \param L size of unit cell
  */
ftype wraparound(ftype coord, ftype L);

#endif // PASSAP_PARTICLE_OPERATIONS_HXX
