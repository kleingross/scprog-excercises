#include "DerivativeArray.h"
#include <iostream>

DerivativeArray::DerivativeArray()
{
	entries.clear();
}

DerivativeArray::DerivativeArray( const std::vector<Particle>& particle, Environment* environment )
{
	entries.clear();

	//first particle
	//Particle first_entry; //initialized with zeros
	//entries.push_back(first_entry); //first particle cannot move

	//particle 2 to N
	for (int i = 0; i < particle.size(); i++)
	{
		Particle entry;
		entry.position = particle[i].velocity;
		entry.velocity = environment->ComputeForce(particle, i);
		entry.mass = 0;
		entries.push_back(entry);
	}
}

DerivativeArray
operator + ( const DerivativeArray& d1, const DerivativeArray& d2 )
{
	DerivativeArray result = d1;
	for (int i = 0; i < d1.entries.size(); i++)
	{
		result.entries[i].position = d1.entries[i].position + d2.entries[i].position ;
		result.entries[i].velocity = d1.entries[i].velocity + d2.entries[i].velocity;
		result.entries[i].mass = d1.entries[i].mass + d2.entries[i].mass;
	}
	return result;
}

DerivativeArray
operator * ( double a, const DerivativeArray& d )
{
	DerivativeArray result = d;
	for (int i = 0; i < d.entries.size(); i++)
	{
		result.entries[i].position = a * d.entries[i].position;
		result.entries[i].velocity = a * d.entries[i].velocity;
		result.entries[i].mass = a * d.entries[i].mass;
	}
	return result;
}

std::vector<Particle>
operator + ( const std::vector<Particle>& particle, const DerivativeArray& d )
{
	std::vector<Particle> result = particle;

	for (int i = 0; i < particle.size(); i++)
	{
		result[i].position = particle[i].position + d.entries[i].position;
		result[i].velocity = particle[i].velocity + d.entries[i].velocity;
		result[i].mass = particle[i].mass;
	}
	return result;
}
