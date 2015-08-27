#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Polygon.h"

class Triangle: public Polygon
{
public:
	Triangle();
	
	virtual void setSidesCount(int sidesCount);
	virtual int getSidesCount();
	
	virtual void setSides(double *sides);
	virtual double *getSides();
	
	virtual void setAngles(double *angles);
	virtual double *getAngles();
	
	virtual double perimeter();
	virtual double square();
	
	virtual void print();
};

#endif // TRIANGLE_H
