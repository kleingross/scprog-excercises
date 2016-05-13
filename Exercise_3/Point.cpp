#include "Point.h"
#include <math.h>

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(double x_value, double y_value)
{
	x = x_value;
	y = y_value;
}

double Point::distance_to(const Point & p1)
{
	double result = 0.0;
	result = sqrt( pow(x - p1.x, 2) + pow(y - p1.y, 2) );
	return result;
}