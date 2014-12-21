
#include "system.hxx"
#include "particle_operations.hxx"

int setup_system(){

  return 0;  
}

int run_system(){

  // BUG: These should be set in the setup_system() and then
  // passed to this function.
  std::array<particle, 999> system;
  ftype maxtime = 100.0;
  const unsigned int num = 400;


  
  ftype coltime[][num] = {{0, 0}, {0, 0}}; // table of collision times
  ftype dt = 0;                            // time delta to collision
  ftype systime = 0;                       // system time
  unsigned int a = 0;                      // first collision partner
  unsigned int b = 0;                      // second collision partner

  while(systime < maxtime){

    // (a) locate next collision

    // TODO: 1) parallelise (trivial in openmp)
  
    /* TODO: 2) Pararellise for mpi as well (multinode):
     *
     * On N nodes (numbered 0:N - 1):
     *
     * Divide full working set into 2*N partitions, numbered 0:2*N-1.
     * To rank n assign partitions n and 2*N - 1 - n as working set.
     * 
     * Communicate dt and colliding pair to an arbiter rank (or all)
     * then determine smallest dt and perform collision.
     *
     * Need to do this to balance load because we only need to
     * calculate collision time for each pair once.
     */

    // num is number of 
    for(unsigned int ii = 0; ii < num ; ii++){
      for(unsigned int jj = ii + 1; jj < num; jj++){
        coltime[ii][jj] = calculate_collision_time(system[ii], system[jj]);
        // TODO: smallest coltime -> dt
      }
    }
  
    // (b) move all particles forward until collision occurs

    // TODO: parallelise (trivial in openmp, (probably) don't in mpi)
    for(unsigned int ii = 0; ii < num; ii++){
      update_position(system[ii], dt);
    }
  
    // (c) collision dynamics for the colliding pair(s)
    perform_collision(&system[a], &system[b]);

    // (d) calulate properties of interest, ready for averaging, before returning to (a)
    // TODO: calculate.
    // Also, consistency checks.

  }
  
  return 0;
}

int evaluate_result(){

  return 0;
}

int print_result(){

  return 0;
}

