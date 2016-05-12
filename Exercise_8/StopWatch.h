#ifndef STOPWATCH_H_
#define STOPWATCH_H_


#include <chrono>


class StopWatch
{
public:
                        StopWatch();

    void                start();
    void                stop();
    
    double              accumulated_time() const;
};

inline
StopWatch::StopWatch()
{
}

inline void
StopWatch::start()
{
}

inline void
StopWatch::stop()
{
}

inline double
StopWatch::accumulated_time() const
{
}


#endif /*STOPWATCH_H_*/
