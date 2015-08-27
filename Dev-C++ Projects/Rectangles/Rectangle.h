#ifndef RECTANGLE_H
#define RECTANGLE_H

struct Point
{
	int x;
	int y;
};

class Rectangle
{
public:
//	Rectangle();
	Rectangle(Point ldc, Point ruc);
	Rectangle(const Rectangle &rect);
//	~Rectangle();
	
	void setLeftDownCorner(Point ldc);
	Point getLeftDownCorner();
	
	void setRightUpCorner(Point ruc);
	Point getRightUpCorner();	
	
	void move(int x, int y);
	
	void changeSize(int dx, int dy);
	
	Rectangle makeUnitedRect(Rectangle r1, Rectangle r2);
	
	Rectangle makeCommonRect(Rectangle r1, Rectangle r2);
	
private:
	Point _leftDownCorner;
	Point _rightUpCorner;
};

#endif // RECTANGLE_H
