
#include <iostream>

// local includes
#include "system.hxx"

#include "vector_math.hxx"

#include "particle_operations.hxx"

int main(){
  std::cout << "Hello world!\n";
  // TODO: init mpi

  const int num = 50;
  particle * system = setup_system();

  for(unsigned int ii = 0; ii < num; ii++){
    std::cout << "particle: " << ii << "\n";
    print_particle(system[ii]);
  }
  return 0;
  run_system(system, num);
  
  evaluate_result();

  print_result();
  
  delete[] system;
  // TODO: close mpi
  
  return 0;
}
