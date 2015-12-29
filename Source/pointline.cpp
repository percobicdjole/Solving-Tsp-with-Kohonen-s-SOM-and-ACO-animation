#include "pointline.h"

PointLine::PointLine(Point* a, Point* b) : a(a), b(b)
{

}

QRectF PointLine::boundingRect() const
{
    return QRectF();
}

void PointLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::darkBlue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(a->getX(), a->getY(), b->getX(), b->getY());
}

void PointLine::advance(int phase)
{
    if (!phase) return;
	return;
}
