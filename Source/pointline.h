#ifndef POINTLINE_H
#define POINTLINE_H

#include <QGraphicsItem>
#include "point.h"

class PointLine : public QGraphicsItem
{
public:
    PointLine(Point* a, Point* b);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
protected:
    void advance(int phase);
private:
    Point* a;
    Point* b;
signals:

public slots:
};

#endif // POINTLINE_H
