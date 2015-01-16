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

#endif // PASSAP_PARTICLE_OPERATIONS_HXX
