
#include <iostream>

// local includes
#include "system.hxx"

#include "vector_math.hxx"

int main(){
  std::cout << "Hello world!\n";
  // TODO: init mpi

  setup_system();
  
  run_system();
  
  evaluate_result();

  print_result();
  
  // TODO: close mpi
  
  return 0;
}
