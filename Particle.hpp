
#ifndef particle_hpp
#define particle_hpp

#include <stdio.h>
#include <vector>
#include <math.h>
#include "Image.hpp"
using namespace std;
/*

particles.hpp

This file contains the particle class, which is used to determine the location of a single particle based on time spent. It serves both for simulating the waterfall and the splash at the bottom.

Author: Fabio von Schelling and Harry Zhou

Collaborators: This code adapts part of John Bost's work.

*/class Particle{

    
private:
    bool bounce;
    vector<float*> color;
    float radius;
    float velocity;
    float time_of_creation;
    float location[3];
    float dist; //how far horizontally could one steam particle move
    void update_x(float);
    void update_y(float);
    void update_z(float);
    
    //instance variables and private helper functions go here
    
public:
    
    ~Particle();
    float get_location_hori(float);
    float get_location_vert(float, float);
    vector<float *> get_color();
    float get_radius();
    float get_dist();
    bool get_bounce();
    Particle(int start, int top, int width, int height, float corrective_factor, bool lock_splash);
    Particle(float tm, int start, int top, int width, int height, float corrective_factor, bool lock_splash);
    void setup(float tm, bool newParticle, int start, int top, int width, int height, float corrective_factor, bool lock_splash);
};

#endif /* Particle_hpp */
