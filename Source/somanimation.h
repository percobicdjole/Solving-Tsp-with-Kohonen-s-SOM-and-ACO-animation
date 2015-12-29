#ifndef SOMANIMATION_H
#define SOMANIMATION_H

#include "KohonenNetwork.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QWidget>
#include "node.h"
#include "point.h"
#include "pointline.h"

class somAnimation : public QGraphicsItem
{
public:
    somAnimation(int, float**, QGraphicsScene*);
    ~somAnimation();
    QRectF boundingRect() const { return QRectF(); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {}
protected:
    void advance(int phase);
private:
    void finish();
    KohonenNetwork Net;
    int NUMBER_OF_NEURONS;
    float** weights;
    Point** graphicsPoint;
    PointLine** graphicsLine;
    QGraphicsScene* scene;
    int counter;
signals:
public slots:
};

#endif // SOMANIMATION_H
