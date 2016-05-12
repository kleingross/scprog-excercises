#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_


#include "Particle.h"
/*#include "Force.h"*/

#include <vector>


class Integrator
{
public:
    virtual                         ~Integrator() {}
    
    // Given particles at time t, compute particles at time t+time_step
    virtual std::vector<Particle>   update_particles( const std::vector<Particle>& particle, double time_step ) = 0;
};


#endif /*INTEGRATOR_H_*/
