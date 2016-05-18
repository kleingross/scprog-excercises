#ifndef EULERINTEGRATOR_H_
#define EULERINTEGRATOR_H_


#include "Particle.h"
#include "Integrator.h"
#include "Environment.h"
#include <string>
#include <vector>


class EulerIntegrator:
    public Integrator
{
public:
    std::vector<Particle>   update_particles( const std::vector<Particle>& particle, double time_step, Environment* environment );
};


#endif /*EULERINTEGRATOR_H_*/
