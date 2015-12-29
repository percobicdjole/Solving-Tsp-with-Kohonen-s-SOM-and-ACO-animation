#ifndef ANTSIM_H
#define ANTSIM_H

class AntSim;

#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "node.h"
#include "edge.h"
#include "PheromoneGraph.h"
#include <QGraphicsScene>
#include <QGraphicsView>

#include "ant.h"

class AntSim : public QGraphicsItem
{
public:
	AntSim(const int antNum, QGraphicsScene*& scene, Edge***& graphicsEdge);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setStartingPos(const float startX, const float startY);
    void setStartingCoords(const float startX, const float startY);
    void SetEndCoords(const float endX, const float endY);
    QPainterPath shape() const Q_DECL_OVERRIDE;
    friend class Aco;
protected:
    void advance(int phase);
private:
    float n, k;
    qreal speed;
	void finish();
    bool isFinishNode();
    bool isFinishNodeCheck();
    QPointF Spoint;
    QPointF Epoint;
    int counter;
    int counterOfIterations;
    int antNumber;
    static PheromoneGraph* antGraph;
    static float** X;
    static Ant* bestAnt;
    static int numberOfAntsFinished;
    static Node** graphicsNode;
    Edge***& graphicsEdge;
    QGraphicsScene*& scene;
    static Edge** finalEdges;
    bool inVerticeFlag;
signals:

public slots:
};

#endif // ANTSIM_H
