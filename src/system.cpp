#include <iostream>
#include "system.hxx"
#include "particle_operations.hxx"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h> 
#include "vector_math.hxx"

const ftype L = 1;

particle * setup_system(){
  ftype x, y, z;
  ftype sigma;
  int num;
  std::string temp;
  std::vector<std::string> items;
  std::ifstream inputFile;
  particle * particles;
  int kk = 0;

  inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit );
  try {
    inputFile.open("particles_file.txt");
    std::string line="";
    while (! inputFile.eof() ){
      getline(inputFile, line); 
      std::stringstream linestream(line);
      int ll = 0;
      while ( ! linestream.eof() && getline(linestream, temp, '\t')){
        items.push_back(temp);
      }
      inputFile.peek();
    }
    unsigned int num;
    num = atoi(items[0].c_str());
    ftype sigma = std::stod (items[1]);
    //std::cout << "num : " << num << " sigma: " << sigma << " size: " << items.size() << "\n"; 
    particles = new particle[num];
    int n = 0;
    for(int ii = 0; ii < num; ii++){
      n = 2 + ii * 6;
      particles[ii].pos.x = std::stod (items[n + 0]);
      particles[ii].pos.y = std::stod (items[n + 1]);
      particles[ii].pos.z = std::stod (items[n + 2]);
      particles[ii].vel.x = std::stod (items[n + 3]);
      particles[ii].vel.y = std::stod (items[n + 4]);
      particles[ii].vel.z = std::stod (items[n + 5]);
    }

  }
  catch (std::ifstream::failure e){
    std::cout << "Exception opening/reading particles file \n";
    std::cerr << "exception caught: " << e.what() << '\n';
    return 0;
  }

  inputFile.close();
  for(unsigned int ii = 0; ii < num; ii++){
     print_particle(particles[ii]);
  }

  return particles;
}

/*
  particles[0].pos.x = 0.5;
  particles[0].pos.y = 0;
  particles[0].pos.z = 0;

  particles[0].vel.x = 0.1;
  particles[0].vel.y = 0;
  particles[0].vel.z = 0;

  particles[1].pos.x = 0;
  particles[1].pos.y = 0;
  particles[1].pos.z = 0;

  particles[1].vel.x = -0.1;
  particles[1].vel.y = 0;
  particles[1].vel.z = 0;

*/




int run_system(particle * system, const int num){


  // BUG: These should be set in the setup_system() and then
  // passed to this function.
  //const unsigned int num = 400;
  //std::array<particle, num> system;
  //system = setup_system();
  ftype maxtime = 10.0;

  
  ftype ** coltime;// = {{0, 0}, {0, 0}}; // table of collision times
  coltime = new ftype*[num];
  for(unsigned int ii = 0; ii < num; ii++){
    coltime[ii] = new ftype[num];
  }
  ftype dt = -1;                           // time delta to collision
  ftype systime = 0;                       // system time
  unsigned int a = 0;                      // first collision partner
  unsigned int b = 0;                      // second collision partner
  unsigned int maxiter = 1000;             // max iterations
  unsigned int iter = 0;

  while(systime < maxtime && iter < maxiter){
    dt = -1;
    iter++;
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
    // smallest coltime -> dt
    // coltime[ii][jj] = calculate_collision_time(system[ii], system[jj]);

    for(unsigned int ii = 0; ii < num ; ii++){
      for(unsigned int jj = ii + 1; jj < num; jj++){
        ftype tmp = -1;
        //std::cout << "particles " << ii << " " << jj << "\n";
        //print_particle(system[ii]);
        //print_particle(system[jj]);
        for(int z=-L; z<=L; z += L){
	  for(int x=-L; x<=L; x += L){
	    for(int y=-L; y<=L; y += L){
	      tmp = calculate_collision_time(system[ii], mirror(system[jj], x, y, z));
              if (tmp > 0){
	        coltime[ii][jj] = tmp;
		if (tmp < dt || dt < 0){
                  dt = tmp;
                  a = ii;
                  b = jj;
                }
	      }
	    }
	  }
        }
      }
    }

    // (b) move all particles forward until collision occurs


    std::cout << "dt: " << dt << " a: " << a << " b: " << b << "\n";
    // TODO: parallelise (trivial in openmp, (probably) don't in mpi)
    for(unsigned int ii = 0; ii < num; ii++){
      update_position(&system[ii], dt, L);
      //std::cout << "updated " << ii << ":\n";
      print_particle(system[ii]);
    }

    // (c) collision dynamics for the colliding pair(s)
    //std::cout << "perform_collision\n";
    perform_collision(&system[a], &system[b]);

    //std::cout << "updated " << a << ":\n";
    //print_particle(system[a]);
    //std::cout << "updated " << b << ":\n";
    //print_particle(system[b]);

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

particle mirror(particle pp, int x, int y, int z){
  pp.pos.x += x;
  pp.pos.y += y;
  pp.pos.z += z;
  return pp;
}

int * evaluate_result(particle * pp, int n){
  //int x = pow(n, 2) - n;
  int * distances = new int[100];
  for(int ii = 0; ii < 100; ii++){
    distances[ii] = 0;
  }

  for(int ii = 0; ii < n; ii++)
    for(int jj = 0; jj < n; jj++){
      if (ii != jj){
        ftype dist = distanceof(pp[ii].pos, pp[jj].pos);
        distances[(int)floor(dist*n)] +=1;
      }
    }
  return distances;
}

int print_result(){

  return 0;
}

