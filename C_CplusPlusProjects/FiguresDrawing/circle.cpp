#include "circle.h"

Circle::Circle(QGraphicsScene *parent)
{
    _mainWidget = parent;
}

void Circle::advance(int phase)
{
    if (phase)
    {
        _mainWidget->addEllipse(QRectF(0.5 * (_mainWidget->width() - _mainWidget->height()), 0.0, _mainWidget->height(),
                                       _mainWidget->height()));
    }
}
