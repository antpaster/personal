#include "Rectangle.h"

Rectangle::Rectangle(Point ldc, Point ruc)
{
	_leftDownCorner = ldc;
	_rightUpCorner = ruc;
}

Rectangle::Rectangle(const Rectangle &rect)
{
	_leftDownCorner = rect._leftDownCorner;
	_rightUpCorner = rect._rightUpCorner;
}
void Rectangle::setLeftDownCorner(Point ldc)
{
	_leftDownCorner = ldc;
}

Point Rectangle::getLeftDownCorner()
{
	return _leftDownCorner;
}

void Rectangle::setRightUpCorner(Point ruc)
{
	_rightUpCorner = ruc;
}

Point Rectangle::getRightUpCorner()
{
	return _rightUpCorner;
}

void Rectangle::move(int x, int y)
{
	_leftDownCorner.x += x;
	_rightUpCorner.x += x;
	_leftDownCorner.y += y;
	_rightUpCorner.y += y;
}

void Rectangle::changeSize(int dx, int dy)
{
	_rightUpCorner.x += dx;
	_rightUpCorner.y += dy;
}

Rectangle Rectangle::makeUnitedRect(Rectangle r1, Rectangle r2)
{
	Rectangle resultRect;
	Point tempPoint;
	
	r1.getLeftDownCorner().x < r2.getLeftDownCorner().x ? tempPoint.x = r1.getLeftDownCorner().x : tempPoint.x = r2.getLeftDownCorner().x;
	r1.getLeftDownCorner().y < r2.getLeftDownCorner().y ? tempPoint.y = r1.getLeftDownCorner().y : tempPoint.y = r2.getLeftDownCorner().y;
	resultRect.setLeftDownCorner(tempPoint);
	
	r1.getRightUpCorner().x < r2.getRightUpCorner().x ? tempPoint.x = r2.getRightUpCorner().x : tempPoint.x = r1.getRightUpCorner().x;
	r1.getRightUpCorner().y < r2.getRightUpCorner().y ? tempPoint.y = r2.getRightUpCorner().y : tempPoint.y = r1.getRightUpCorner().y;
	resultRect.setRightUpCorner(tempPoint);
	
	return resultRect;
}

Rectangle Rectangle::makeCommonRect(Rectangle r1, Rectangle r2)
{
	Rectangle resultRect;
	Point tempPoint;
	
	r1.getLeftDownCorner().x < r2.getLeftDownCorner().x ? tempPoint.x = r2.getLeftDownCorner().x : tempPoint.x = r1.getLeftDownCorner().x;
	r1.getLeftDownCorner().y < r2.getLeftDownCorner().y ? tempPoint.y = r2.getLeftDownCorner().y : tempPoint.y = r1.getLeftDownCorner().y;
	resultRect.setLeftDownCorner(tempPoint);
	
	r1.getRightUpCorner().x < r2.getRightUpCorner().x ? tempPoint.x = r1.getRightUpCorner().x : tempPoint.x = r2.getRightUpCorner().x;
	r1.getRightUpCorner().y < r2.getRightUpCorner().y ? tempPoint.y = r1.getRightUpCorner().y : tempPoint.y = r2.getRightUpCorner().y;
	resultRect.setRightUpCorner(tempPoint);
	
	return resultRect;
}
