#include "square.h"

Square::Square(QGraphicsScene *parent)
{
    _mainWidget = parent;
}

void Square::advance(int phase)
{
    if (phase)
    {
        _mainWidget->addRect(QRectF(0.5 * (_mainWidget->width() - _mainWidget->height()), 0.0, _mainWidget->height(),
                                    _mainWidget->height()));
    }
}
