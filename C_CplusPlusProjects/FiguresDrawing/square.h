#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

class Square : public Figure
{
private:
    QGraphicsScene *_mainWidget;

public:
    Square(QGraphicsScene *parent);
    Square() {};
    //virtual ~Square() {};
    virtual void advance(int phase) override;
};

#endif // SQUARE_H
