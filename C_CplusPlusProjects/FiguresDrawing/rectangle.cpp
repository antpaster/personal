#include "rectangle.h"

Rectangle::Rectangle(QGraphicsScene *parent)
{
    _mainWidget = parent;
}

void Rectangle::advance(int phase)
{
    if (phase)
    {
        _mainWidget->addRect(_mainWidget->sceneRect());
    }
}
