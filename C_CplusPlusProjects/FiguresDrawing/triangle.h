#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

class Triangle : public Figure
{
private:
    QGraphicsScene *_mainWidget;

public:
    Triangle(QGraphicsScene *parent);
    Triangle() {};
    //virtual ~Triangle() {};
    virtual void advance(int phase) override;
};

#endif // TRIANGLE_H
