#ifndef SECONDORDERRUNGEKUTTAINTEGRATOR_H_
#define SECONDORDERRUNGEKUTTAINTEGRATOR_H_


#include "Particle.h"
#include "Integrator.h"

#include <vector>


class SecondOrderRungeKuttaIntegrator:
    public Integrator
{
public:
    virtual std::vector<Particle>   update_particles( const std::vector<Particle>& particle, double time_step );
};


#endif /*SECONDORDERRUNGEKUTTAINTEGRATOR_H_*/
