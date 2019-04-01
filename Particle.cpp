
#include "Particle.hpp"

Particle::Particle(int start, int top, int width, int height, float corrective_factor, bool lock_splash){
    setup(0, true, start, top, width, height, corrective_factor, lock_splash);
}

Particle::Particle(float tm, int start, int top, int width, int height, float corrective_factor, bool lock_splash){
    setup(tm, true, start, top, width, height, corrective_factor, lock_splash);
}

void Particle::setup(float tm, bool newParticle, int start, int top, int width, int height, float corrective_factor, bool lock_splash){ //main construction/reconstruction method based on given boolean
    if(newParticle){
        bounce = false;
        color.push_back(new float (1));
        color.push_back(new float (1));
        color.push_back(new float (1));
        location[0] = start + 5 + ((width - 10) * (float(rand()) / float(RAND_MAX)));
        location[1] = float(top); //y axis delimited by top
        location[2] = float(-10);
        radius = 1;
        dist = (-width/2) + (rand() % (width));
    }
    else{
        location[0] = start + 5 + ((width - 10) * (float(rand()) / float(RAND_MAX)));
        if (bounce || lock_splash){
            bounce = false;
            location[1] = float(top);
        }
        else{
            bounce = true;
            location[1] = top + height - corrective_factor;
        }
    }
    velocity = ((rand() % 200) + 100);
    time_of_creation = tm;
}

Particle::~Particle(){ //free allocated particle memory
    while(color.size() != 0){
        delete(color.back());
        color.pop_back();
    }
}

float Particle::get_location_hori(float tm){ //based on given time in correspondence to time of creation
    float time_difference = tm - time_of_creation;
    if (!bounce) return location[0];
    else if (dist > 0){
        return location[0] + velocity * time_difference;
    }
    else{
        return location[0] - velocity * time_difference;
    }
}

float Particle::get_location_vert(float tm, float widening_factor){ //based on given time in correspondence to time of creation
    float time_difference = tm - time_of_creation;
    if (!bounce){
        location[2] *= widening_factor;
        return float (location[1] + velocity * pow(time_difference, 2) + velocity * time_difference);
    }
    float h;
    if (dist > 0){
        h = (-pow((velocity*time_difference - dist),2) + pow(dist,2))/20;
    }
    else{
        h = (-pow((velocity*time_difference + dist),2) + pow(dist,2))/20;
    }
    return location[1] - h;
}

vector<float *> Particle::get_color() {
    return color;
}

float Particle::get_radius(){
    return radius;
}

void Particle::update_x(float x) {
    this->location[0] = x;
}

void Particle::update_y(float y) {
    this->location[1] = y;
}

void Particle::update_z(float z) {
    this->location[2] = z;
}

bool Particle::get_bounce(){
    return bounce;
}

float Particle::get_dist() {
    return dist;
}


