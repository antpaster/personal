#include "triangle.h"

Triangle::Triangle(QGraphicsScene *parent)
{
    _mainWidget = parent;
}

void Triangle::advance(int phase)
{
    if (phase)
    {
        _mainWidget->addPolygon(QPolygonF(QVector<QPointF>
                                          {
                                              QPointF(0.5 * _mainWidget->width(), 0.0),
                                              QPointF(0.5 * (_mainWidget->width() - _mainWidget->height()) + _mainWidget->height(),
                                              _mainWidget->height()),
                                              QPointF(0.5 * (_mainWidget->width() - _mainWidget->height()), _mainWidget->height()),
                                          }));
    }
}
