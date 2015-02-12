#include "setup_system.hxx"
#include "system.hxx"
#include <iostream>
#include <fstream>
#include <math.h> 

#include <random>

const ftype L = 1;

int main(){
  ftype x, y, z, delta;
  int num;
  ftype sigma;
  bool collided = false;

  std::random_device rd;
  std::default_random_engine el(rd());

  std::uniform_real_distribution<ftype> position_dist(0,1);
  std::uniform_real_distribution<ftype> velocity_dist(-0.5,0.5);


  std::cout << "\n Enter number of particles: ";
  std::cin >> num;

  std::cout << "\n Enter particle's diameter: ";
  std::cin >> sigma;

  particle * particles = new particle[num];
  int n = 0;
  
  while ( n < num){
    collided = false;
    x = ((ftype) position_dist(el));
    y = ((ftype) position_dist(el));
    z = ((ftype) position_dist(el));
    particles[n].pos.x = x;
    particles[n].pos.y = y;
    particles[n].pos.z = z;
    x = ((ftype) velocity_dist(el));
    y = ((ftype) velocity_dist(el));
    z = ((ftype) velocity_dist(el));
    particles[n].vel.x = x;
    particles[n].vel.y = y;
    particles[n].vel.z = z;
    for(int i=0; i < n; i++){

      for(int z=-L; z<=L; z += L){
        for(int x=-L; x<=L; x += L){
          for(int y=-L; y<=L; y += L){
            delta = calculate_delta(particles[n], mirror(particles[i], x, y, z));
            if ( sqrt(delta) <= sigma + 0.0001 ){
              collided = true;
              break;
            }
          }
          if(collided) break;
          }
        if(collided) break;
        }
      if(collided) break;
      } 
    if(!collided){
      std::cout << "pos: " << particles[n].pos.x << " " <<  particles[n].pos.y << " " << particles[n].pos.z << "\t\t"
                << "vel: " << particles[n].vel.x << " " <<  particles[n].vel.y << " " << particles[n].vel.z << "\n";
      n++;
    }
    
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

ftype calculate_delta(particle p1, particle p2){
 return (pow(p1.pos.x - p2.pos.x, 2)) + (pow(p1.pos.y - p2.pos.y, 2)) + (pow(p1.pos.z - p2.pos.z, 2));
}

