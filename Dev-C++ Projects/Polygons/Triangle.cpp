#include "Triangle.h"
#include "math.h"
#include <iostream>

using namespace std;

double Triangle::perimeter()
{
	double result = 0;
	for (int i = 0; i < this->getSidesCount(); i++)
		result += this->getSides()[i];
	return result;
}

double Triangle::square()
{
	return 0.5 * this->getSides()[0] * sin(this->getAngles()[0]) * this->getSides()[1];
}

void Triangle::print()
{
	cout << "--------------------Triangle's data-------------------\n";
	cout << "Sides:\n";
	for (int i = 0; i < this->getSidesCount(); i++)
		cout << "Side " << i + 1 << " size: " << this->getSides()[i] << endl; 
	cout << "Angles:\n";
	for (int i = 0; i < this->getSidesCount(); i++)
		cout << 3 % i + 1 << " ^ " << 3 % i + 2 << " angle: " << this->getAngles()[i] << endl; 
}
