#ifndef EULERINTEGRATOR_H_
#define EULERINTEGRATOR_H_


#include "Particle.h"
#include "Integrator.h"

#include <vector>


class EulerIntegrator:
    public Integrator
{
public:
    virtual std::vector<Particle>   update_particles( const std::vector<Particle>& particle, double time_step );
};


#endif /*EULERINTEGRATOR_H_*/
