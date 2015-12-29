#include "point.h"

Point::Point(const int pointNum, const float x, const float y)
{
    number = pointNum;
    posX = x;
    posY = y;
    setPos(posX, posY);
}

void Point::advance(int phase)
{
    if (!phase) return;
    setPos(posX, posY);
    update();
}

void Point::setPosition(const float x, const float y)
{
    posX = x;
    posY = y;
}

QRectF Point::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::darkBlue);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 5, 5);

    painter->setBrush(brush);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 5, 5);
}

QPainterPath Point::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 5, 5);
    return path;
}
