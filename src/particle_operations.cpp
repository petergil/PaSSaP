#include "particle_operations.hxx"
#include "datatypes.hxx"
#include "vector_math.hxx"
#include <math.h>
#include <iostream>

const ftype SIGMA = 0.1; 

void print_particle(const particle &p){

  std::cout << "pos: " << p.pos.x << " " << p.pos.y << " " << p.pos.z << "\n";
  std::cout << "vel: " << p.vel.x << " " << p.vel.y << " " << p.vel.z << "\n";

}

ftype calculate_collision_time(const particle &a, const particle &b){
  std::cout << "calculate_collision_time\n"; 
  // T_ab is time of collision 
  ftype T_ab;

  // r(a,b) = r(a) - r(b)
  // r is the position
  vector3 R_ab;
  R_ab = sub(a.pos, b.pos);
  
  // v(a,b) = v(a) - v(b)
  // v is the velocity 
  vector3 V_ab;
  V_ab = sub(a.vel, b.vel);

  // b(a,b) = r(a,b) * v(a,b)
  // b is the Dot Product
  ftype B_ab;
  B_ab = dot(R_ab, V_ab);
  
  if (B_ab < 0){
    // delta = b(a,b)^2 - v(a,b)^2 * (r(a,b)^2 - sigma^2)
    // t(a,b) = (-b(a,b) - sqrt(delta)) / v(a,b)^2
    //
    // V_ab_pow2 is V_ab power 2
    // B_ab_pow2 is B_ab power 2
    // R_ab_pow2 is R_ab power 2
    //
    ftype V_ab_pow2;
    ftype B_ab_pow2;
    ftype R_ab_pow2;
  
    V_ab_pow2 = dot(V_ab, V_ab);
    B_ab_pow2 = B_ab * B_ab;
    R_ab_pow2 = dot(R_ab, R_ab);

    if( pow(B_ab, 2) - V_ab_pow2 * (R_ab_pow2 - pow(SIGMA, 2)) >= 0){  
      ftype delta = B_ab_pow2 - V_ab_pow2 * (R_ab_pow2 - pow(SIGMA, 2));
      T_ab = (-B_ab - sqrt(delta)) / V_ab_pow2;
    } else{ // complex roots, no collision
       T_ab = -1;
    }
  }
  else{
    T_ab = -1;
  }

  if(T_ab != T_ab || T_ab >= 0){
    std::cout << "a:\n";
    print_particle(a);
    std::cout << "b:\n";
    print_particle(b);
    std::cout << "Time: " << T_ab << "\n";
  }
  return T_ab;
}

ftype wraparound(ftype coord, ftype L){
  if (coord < 0){
    coord = L + coord;
  }

  return coord;
}

void update_position(particle *par, ftype dt, ftype L){
  std::cout << "p.x " << par->pos.x << " p.v " << par->vel.x*dt<<"\n";
  std::cout << "fmod " << fmod(par->pos.x + par->vel.x * dt, L) <<"\n";
  par->pos.x = wraparound(fmod(par->pos.x + par->vel.x * dt, L), L);

  std::cout << "p.x " << par->pos.x << " p.v " << par->vel.x*dt<<"\n";
  par->pos.y = wraparound(fmod(par->pos.y + par->vel.y * dt, L), L);
  par->pos.z = wraparound(fmod(par->pos.z + par->vel.z * dt, L), L);


}

void perform_collision(particle *a, particle *b){
  vector3 R_ab;
  vector3 V_ab;
  ftype B_ab;

  R_ab = sub(a->pos, b->pos);
  V_ab = sub(a->vel, b->vel);
  B_ab = dot(R_ab, V_ab);
  vector3 dv = multiply(-(B_ab / pow(SIGMA, 2)), R_ab);

  a->vel = add(a->vel, dv);
  b->vel = sub(b->vel, dv);
}
