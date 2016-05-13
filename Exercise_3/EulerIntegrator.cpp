#include "EulerIntegrator.h"
#include "DerivativeArray.h"

EulerIntegrator::EulerIntegrator()
{
	integrator_type = "Euler";
}

std::vector<Particle>
EulerIntegrator::update_particles( const std::vector<Particle>& particle, double time_step )
{
	std::vector<Particle> new_particle = particle;
	DerivativeArray Derivative(particle);
	new_particle = particle + (time_step * Derivative);
	return new_particle;
}
