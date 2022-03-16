#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>


class Figure : public QGraphicsEllipseItem
{
private:
    QGraphicsScene *_mainWidget;

public:
    Figure(QGraphicsScene *parent);
    Figure() {};
    //virtual ~Figure() {};
    virtual void advance(int phase) = 0;
};

#endif // FIGURE_H
