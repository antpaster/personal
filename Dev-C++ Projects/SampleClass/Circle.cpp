#include <iostream>
#include "Circle.h"

using namespace std;

Circle::Circle()
{
	this->center.x = 0;
	this->center.y = 0;
	this->radius = 5;
}

Circle::Circle(Point center, int radius)
{
	this->center = center;
	this->radius = radius;
}

void Circle::setRadius(int radius)
{
	this->radius = radius;
}

int Circle::getRadius()
{
	return this->radius;
}

ostream& operator <<(ostream& out, Circle& C)
{
	out << '(' << C.center.x << ", " << C.center.y << ") " << C.radius;
	return out;
}
