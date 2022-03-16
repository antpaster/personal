#ifndef CIRCLE_H
#define CIRCLE_H

#include "figure.h"

class Circle : public Figure
{
private:
    QGraphicsScene *_mainWidget;

public:
    Circle(QGraphicsScene *parent);
    Circle() {};
    //virtual ~Circle() {};
    virtual void advance(int phase) override;
};

#endif // CIRCLE_H
