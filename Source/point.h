#ifndef POINT_H
#define POINT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Point : public QGraphicsItem
{
public:
    Point(const int pointNum, const float x, const float y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void setPosition(const float x, const float y);
    float getX() { return posX; }
    float getY() { return posY; }
protected:
    void advance(int phase);
private:
    int number;
    float posX, posY;
signals:

public slots:
};

#endif // POINT_H
