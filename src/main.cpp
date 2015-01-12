
#include <iostream>

// local includes
#include "system.hxx"

#include "vector_math.hxx"

int main(){
  std::cout << "Hello world!\n";
  // TODO: init mpi

  const int num = 100;
  particle * system = setup_system(num);
  
  run_system(system, num);
  
  evaluate_result();

  print_result();
  
  // TODO: close mpi
  
  return 0;
}
