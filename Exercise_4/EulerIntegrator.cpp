#include "EulerIntegrator.h"
#include "DerivativeArray.h"


std::vector<Particle>
EulerIntegrator::update_particles( const std::vector<Particle>& particle, double time_step , Environment* environment)
{
	std::vector<Particle> new_particle = particle;
	DerivativeArray Derivative(particle, environment);
	new_particle = particle + (time_step * Derivative);
	return new_particle;
}
