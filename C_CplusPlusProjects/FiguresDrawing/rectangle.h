#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

class Rectangle : public Figure
{
private:
    QGraphicsScene *_mainWidget;

public:
    Rectangle(QGraphicsScene *parent);
    Rectangle() {};
    //virtual ~Rectangle() {};
    virtual void advance(int phase) override;
};

#endif // RECTANGLE_H
