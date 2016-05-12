#ifndef POINT_H_
#define POINT_H_


#include <math.h>


struct Point
{
    double          x;
    double          y;
    
                    Point();
                    Point( double x, double y );
            
    Point&          operator += ( const Point& p );
    Point&          operator -= ( const Point& p );
    Point&          operator *= ( double a );
    Point&          operator /= ( double a );
    
    double          length() const;
    
    static double   Dot( const Point& p1, const Point& p2 );
};

inline Point
operator + ( const Point& p1, const Point& p2 )
{
}

inline Point
operator - ( const Point& p1, const Point& p2 )
{
}

inline Point
operator * ( double a, const Point& p )
{
}

inline Point
operator / ( const Point& p, double a )
{
}


#endif /*POINT_H_*/
