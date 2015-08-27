#ifndef _CIRCLE_H
#define _CIRCLE_H
#include <iostream>

using namespace std;

struct Point
{
	int x, y;
};

class Circle
{
public:
	Circle();
	Circle(Point center, int radius);
	
	void setRadius(int radius);
	int getRadius();
	
	friend ostream& operator <<(ostream& out, Circle& C);

private:
	Point center;
	int radius;
};

#endif //_CIRCLE_H
