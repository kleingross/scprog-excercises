#ifndef PARTICLE_H_
#define PARTICLE_H_


#include "Point.h"


struct Particle
{
    Point   position;
    Point   velocity;
    double  mass;
    
            Particle();
};


#endif /*PARTICLE_H_*/
