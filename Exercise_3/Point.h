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
	double			distance_to( const Point& p1);
	
    static double   Dot( const Point& p1, const Point& p2 );
};

inline Point
operator + ( const Point& p1, const Point& p2 )
{
	Point result;
	result.x = p1.x + p2.x;
	result.y = p1.y + p2.y;
	return result;
}

inline Point
operator - ( const Point& p1, const Point& p2 )
{
	Point result;
	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	return result;
}

inline Point
operator * ( double a, const Point& p )
{
	Point result;
	result.x = a * p.x;
	result.y = a * p.y;
	return result;
}

inline Point
operator / ( const Point& p, double a )
{
	Point result;
	result.x = p.x / a;
	result.y = p.y / a;
	return result;
}


#endif /*POINT_H_*/
