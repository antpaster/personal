#include "Polygon.h"

Polygon::Polygon(int sidesCount)
{
	_sidesCount = sidesCount;
	m_pSides = new double[_sidesCount];
	m_pAngles = new double[_sidesCount];
}

void Polygon::setSidesCount(int sidesCount)
{
	_sidesCount = sidesCount;
}

int Polygon::getSidesCount()
{
	return _sidesCount;
}

void Polygon::setSides(double *sides)
{
	m_pSides = sides;
}

double* Polygon::getSides()
{
	return m_pSides;
}

void Polygon::setAngles(double *angles)
{
	m_pAngles = angles;
}

double* Polygon::getAngles()
{
	return m_pAngles;
}

Polygon::~Polygon()
{
	delete [] m_pSides;
	delete [] m_pAngles;
}
