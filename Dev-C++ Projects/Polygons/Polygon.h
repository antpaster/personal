#ifndef POLYGON_H
#define POLYGON_H

class Polygon
{
public:
	Polygon(int sidesCount);
	~Polygon();	

	void setSidesCount(int sidesCount);
	int getSidesCount();
	
	void setSides(double *sides);
	double *getSides();
	
	void setAngles(double *angles);
	double *getAngles();
	
	virtual double perimeter() = 0;
	virtual double square() = 0;
	
	virtual void print() = 0;
	
private:
	int _sidesCount;
	double *m_pSides;
	double *m_pAngles;
};

#endif // POLYGON_H
