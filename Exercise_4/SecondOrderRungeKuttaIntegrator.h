#ifndef SECONDORDERRUNGEKUTTAINTEGRATOR_H_
#define SECONDORDERRUNGEKUTTAINTEGRATOR_H_


#include "Particle.h"
#include "Integrator.h"
#include "Environment.h"
#include <vector>


class SecondOrderRungeKuttaIntegrator:
    public Integrator
{
public:
    std::vector<Particle>   update_particles( const std::vector<Particle>& particle, double time_step, Environment* environment);
};


#endif /*SECONDORDERRUNGEKUTTAINTEGRATOR_H_*/
