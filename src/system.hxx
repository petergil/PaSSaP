#ifndef PASSAP_SYSTEM_HXX
#define PASSAP_SYSTEM_HXX

#include "datatypes.hxx"
#include <array>


/**
  * Initialize system.
  *
  * TODO: Should either read state from a file or randomly
  * generate a state from a random seed + a desired temperature.
  *
  * \param num number of particles in the system
  *
  * Should return the built system.
  */
particle * setup_system(const int num);

/**
  * Run system.
  *
  * TODO: accept system state as returned from setup_system() as
  * well as maxtime and other constraints. (maybe particle
  * radius?)
  *
  * \param system an array of particles
  * \param num number of particles in the system
  *
  * Should return enough state to evaluate the result of the calulations.
  */
int run_system(particle * system, const int num);

/**
  * Mirroring particle in other cubs.
  *
  * \param pp the particle that we want to move in other cubes
  * \param x pp.pos.x position moves x unit
  * \param y pp.pos.y position moves y unit
  * \param z pp.pos.z position moves z unit
  *
  * Should return particle's new position
  * */
particle mirror(particle pp, int x, int y, int z);

/**
  * Evaluate result.
  *
  * TODO: Look up what results are interesting and then implement
  * calculations.
  */
int evaluate_result();

/**
  * Print result.
  *
  * TODO: Print results from evaluate_result()
  *
  */
int print_result();


#endif // PASSAP_SYSTEM_HXX
