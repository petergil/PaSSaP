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
  * Should return the built system.
  */
int setup_system();

/**
  * Run system.
  *
  * TODO: accept system state as returned from setup_system() as
  * well as maxtime and other constraints. (maybe particle
  * radius?)
  *
  * Should return enough state to evaluate the result of the calulations.
  */
int run_system();

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
