#include "particle.h"
#include "Integrator.h"
#include "EulerIntegrator.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


// Create the Euler integrator, or the second order Runge-Kutta integrator, or the fourth order Runge-Kutta integrator
static Integrator*
CreateIntegrator( int argc, char** argv )
{
	static EulerIntegrator* integrator;
	return integrator;
}

// read particles from the file "particle.txt"
static std::vector<Particle>
ReadParticles()
{
	int N = 4; //number of particles to read
	std::fstream input_file;
	std::vector<Particle> start_particles;
	
	input_file.open("particle.txt");
	for (int i = 0; i < N; i++)
	{
		Particle particle;
		input_file >> particle.position.x >> particle.position.y >> particle.mass;
	}
	input_file.close();

	return start_particles;
}

// print particles to the file frame_NNNN.txt,
// where NNNN is the frame index passed as the second function argument
static void
PrintParticles( const std::vector<Particle>& particle, int frame )
{
		//set up filename from frame, needs optimization
	std::stringstream convert; //conversion int to string
	convert << frame;
	std::string frame_number = convert.str();
	size_t framesize = frame_number.length();
	std::string output_filename = "frame_";		//set up filename
	output_filename.resize(10 - framesize, '0');
	output_filename = output_filename + frame_number + ".txt";

	std::cout << "printed " << output_filename << std::endl; //debug

	std::fstream output_file;
	output_file.open(output_filename, std::ios::out);
	
	//write to output file
	output_file << "hallo welt!" << std::endl;
	output_file.close();
	
	/*
	int N = 4; //number of particles in vector
	for (int i = 0; i < N; i++)
	{
		output_file << print_particle[i].position.x << " " << print_particle[i].position.y << std::endl;
	}
	*/
		
}

static void
RunSimulation( std::vector<Particle>& particle, Integrator* integrator )
{
    static const int    FrameCount  = 500;
    static const int    StepCount   = 10;
    static const double TimeStep    = 0.01;
    
    for( int frame = 0; frame < FrameCount; ++frame )
    {
        for( int step = 0; step < StepCount; ++step )
            particle = integrator->update_particles( particle, TimeStep );
        
        PrintParticles( particle, frame );
    }
}

int
main( int argc, char** argv )
{
	//debug
	std::vector<Particle> particle = ReadParticles();
	PrintParticles(particle, 123);

    Integrator* integrator = CreateIntegrator( argc, argv );
    
    if( integrator != 0 )
    {
        std::vector<Particle> particle = ReadParticles();
        RunSimulation( particle, integrator );
    }

	std::cin.get();
    
    return 0;
}
