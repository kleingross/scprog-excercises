#include "StopWatch.h"

#include <vector>
#include <stdio.h>


std::vector<Disk>
GenerateDisks( double box_length, size_t disk_count, double disk_radius )
{
}

void
UpdateDisks( std::vector<Disk>& disk, double time_step )
{
}

void
ProcessDiskWallCollisions( std::vector<Disk>& disk, double box_length, double disk_radius )
{
}

void
ProcessDiskDiskCollisions( std::vector<Disk>& disk, double disk_radius )
{
}

void
PrintDisks( const std::vector<Disk>& disk, int frame, double disk_radius )
{
}

void
RunSimulation( std::vector<Disk>& disk, double box_length, double disk_radius )
{
    static const int    FrameCount  = 500;
    static const int    StepCount   = 100;
    static const double TimeStep    = 0.001;
    
    StopWatch sw;
    
    for( int frame = 0; frame < FrameCount; ++frame )
    {
        for( int step = 0; step < StepCount; ++step )
        {
            UpdateDisks( disk, TimeStep );
            ProcessDiskWallCollisions( disk, box_length, disk_radius );
            sw.start();
            ProcessDiskDiskCollisions( disk, disk_radius );
            sw.stop();
        }
        
        PrintDisks( disk, frame, disk_radius );
    }
    
    printf( "collision processing time = %.1f ms\n", sw.accumulated_time() );
}

int
main( int argc, char** argv )
{
    if( argc == 3 )
    {
        static const double BoxLength = 1000.0;
        
        size_t disk_count = atoi( argv[1] );
        double disk_radius = atof( argv[2] );
        
        std::vector<Disk> disk = GenerateDisks( BoxLength, disk_count, disk_radius );
        RunSimulation( disk, BoxLength, disk_radius );
    }
    
    return 0;
}
