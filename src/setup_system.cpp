#include "system.hxx"
#include <iostream>
#include <fstream>
#include <math.h> 

#include <random>

int main(){
  ftype x, y, z, delta;
  int num;
  ftype sigma;

  std::random_device rd;
  std::default_random_engine el(rd());

  std::uniform_real_distribution<ftype> uniform_dist(-1,1);

  std::cout << "\n Enter number of particles: ";
  std::cin >> num;

  std::cout << "\n Enter particle's radius: ";
  std::cin >> sigma;

  particle * particles = new particle[num];
  int n = 0;
  while ( n < num){
    x = ((ftype) uniform_dist(el));
    y = ((ftype) uniform_dist(el));
    z = ((ftype) uniform_dist(el));
    particles[n].pos.x = x;
    particles[n].pos.y = y;
    particles[n].pos.z = z;
    x = ((ftype) uniform_dist(el));
    y = ((ftype) uniform_dist(el));
    z = ((ftype) uniform_dist(el));
    particles[n].vel.x = x;
    particles[n].vel.y = y;
    particles[n].vel.z = z;
    for(int i=0; i < n; i++){
      delta = (pow(particles[n].pos.x - particles[i].pos.x, 2)) + (pow(particles[n].pos.y - particles[i].pos.y, 2)) + (pow(particles[n].pos.z - particles[i].pos.z, 2));
      if ( sqrt(delta) <= 2 * sigma){
        n -= 1;
        break;
      }
    }
    n++;
    std::cout << "pos: " << particles[n].pos.x << " " <<  particles[n].pos.y << " " << particles[n].pos.z << "\t\t"
              << "vel: " << particles[n].vel.x << " " <<  particles[n].vel.y << " " << particles[n].vel.z << "\n";
  }

  std::ofstream particles_file;
  particles_file.open ("particles_file.txt");
  particles_file << num << "\t" << sigma << "\n";
  for (int n=0; n < num; n++){
    particles_file <<  particles[n].pos.x << "\t" <<  particles[n].pos.y << "\t" << particles[n].pos.z << "\t" << particles[n].vel.x << "\t" <<  particles[n].vel.y << "\t" << particles[n].vel.z << "\n";
  }
  particles_file.close();

  return 0;
}


