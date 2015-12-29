#include "edge.h"
#include "node.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node(bool color, bool small)
    : color(color), small(small)
{
    setAcceptedMouseButtons(0);      
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

/*void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}*/

/*QList<Edge *> Node::edges() const
{
    return edgeList;
}*/

void Node::advance(int phase)                        // Za neke kasnije
{
	if (!phase) return;
	return;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    if (small == false)
        path.addEllipse(-10, -10, 20, 20);
    else
        path.addEllipse(-10, -10, 5, 5);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)               
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    if (small == false)
        painter->drawEllipse(-7, -7, 20, 20);
    else
        painter->drawEllipse(-7, -7, 5, 5);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        if (color == false)
        {
            gradient.setColorAt(1, QColor(Qt::blue).light(120));
            gradient.setColorAt(0, QColor(Qt::darkBlue).light(120));
        }
        else
        {
            gradient.setColorAt(1, QColor(Qt::green).light(120));
            gradient.setColorAt(0, QColor(Qt::darkGreen).light(120));
        }
    }
    else
    {
        if (color == false)
        {
            gradient.setColorAt(0, Qt::blue);
            gradient.setColorAt(1, Qt::darkBlue);
        }
        else
        {
            gradient.setColorAt(0, Qt::green);
            gradient.setColorAt(1, Qt::darkGreen);
        }
    }
    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    if (small == false)
        painter->drawEllipse(-10, -10, 20, 20);
    else
        painter->drawEllipse(-10, -10, 5, 5);
}

