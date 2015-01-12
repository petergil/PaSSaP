#include <iostream>
#include "system.hxx"
#include "particle_operations.hxx"

particle * setup_system(const int num){
  ftype x, y, z;
  particle particles[num];
  for (int n=0; n < num; n++){
    x = ((ftype) rand() / (RAND_MAX));
    y = ((ftype) rand() / (RAND_MAX));
    z = ((ftype) rand() / (RAND_MAX));
    particles[n].pos.x = x;
    particles[n].pos.y = y;
    particles[n].pos.z = z;
    x = ((ftype) rand() / (RAND_MAX));
    y = ((ftype) rand() / (RAND_MAX));
    z = ((ftype) rand() / (RAND_MAX));
    particles[n].vel.x = x;
    particles[n].vel.y = y;
    particles[n].vel.z = z;
    std::cout << "pos: " << particles[n].pos.x << " " <<  particles[n].pos.y << " " << particles[n].pos.z << "\t\t"
              << "vel: " << particles[n].vel.x << " " <<  particles[n].vel.y << " " << particles[n].vel.z << "\n";
    }

  return particles;  
}

int run_system(particle * system, const int num){

  // BUG: These should be set in the setup_system() and then
  // passed to this function.
  //const unsigned int num = 400;
  //std::array<particle, num> system;
  //system = setup_system();
  ftype maxtime = 100.0;

  
  ftype ** coltime;// = {{0, 0}, {0, 0}}; // table of collision times
  coltime = new ftype*[num];
  for(unsigned int ii = 0; ii < num; ii++){
    coltime[ii] = new ftype[num];
  }
  ftype dt = 1;                            // time delta to collision
  ftype systime = 0;                       // system time
  unsigned int a = 0;                      // first collision partner
  unsigned int b = 0;                      // second collision partner
  unsigned int maxiter = 1000;             // max iterations

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
    systime += dt;

  }
  for(unsigned int ii = 0; ii < num; ii++){
    delete[] coltime[ii];
  }
  delete[] coltime;
  return 0;
}

int evaluate_result(){

  return 0;
}

int print_result(){

  return 0;
}

