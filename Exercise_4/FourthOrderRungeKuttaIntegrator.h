#ifndef FOURTHORDERRUNGEKUTTAINTEGRATOR_H_
#define FOURTHORDERRUNGEKUTTAINTEGRATOR_H_


#include "Particle.h"
#include "Integrator.h"
#include "Environment.h"
#include <vector>


class FourthOrderRungeKuttaIntegrator:
    public Integrator
{
public:
    std::vector<Particle>   update_particles( const std::vector<Particle>& particle, double time_step, Environment* environment);
};


#endif /*FOURTHORDERRUNGEKUTTAINTEGRATOR_H_*/
