#include "antsim.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <cmath>
#include <iostream>
#include <QWidget>
#include <QTime>
#include <QLayout>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QDialog>
#include <QtCore>
#include <QtWidgets>

using namespace heuristic_constants;

PheromoneGraph* AntSim::antGraph = nullptr;
float** AntSim::X = nullptr;
Ant* AntSim::bestAnt = nullptr;
int AntSim::numberOfAntsFinished = 0;
Node** AntSim::graphicsNode = nullptr;
Edge**  AntSim::finalEdges = nullptr;
//Edge*** AntSim::graphicsEdge = nullptr;

AntSim::AntSim(const int antNum, QGraphicsScene*& scene, Edge***& graphicsEdge) : scene(scene), graphicsEdge(graphicsEdge)	// U sceni se pointeri mijenjaju
{
    setAcceptedMouseButtons(0);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    speed = 10;
    counter = 0;
    counterOfIterations = 0;
    k = 0;
    n = 0;
    antNumber = antNum;
	finalEdges = nullptr;
    int z = antGraph->ant[antNumber].edge;
    setStartingPos(X[z][0], X[z][1]);
    inVerticeFlag = true;
}

void AntSim::setStartingPos(const float startX, const float startY)
{
    Spoint.setX(startX);
    Spoint.setY(startY);
    Epoint.setX(startX);
    Epoint.setY(startY);
    setPos(startX, startY);
}

void AntSim::setStartingCoords(const float startX, const float startY)
{
    Spoint.setX(startX);
    Spoint.setY(startY);
    setPos(startX, startY);
}

void AntSim::SetEndCoords(const float endX, const float endY)
{
    Epoint.setX(endX);
    Epoint.setY(endY);
}

QRectF AntSim::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath AntSim::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void AntSim::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::green);
    if (!isFinishNodeCheck())
        brush.setColor(Qt::black);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 10, 10);

    painter->setBrush(brush);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 10, 10);
}

void AntSim::advance(int phase)        
{										// neki od itema zajebava kada mu se zove advance, vjerovatno je on sam greska... moze biti i da je u advance
    if (!phase || k >= INFINITI || k <= -INFINITI || n >= INFINITI || n <= -INFINITI) return;

    if (!isFinishNode())
    {
        float z = k;
        z = cos(atan(z))*(speed);
        if (Spoint.x() > Epoint.x())
            z = -z;
        z+= this->pos().x();
        float y = k*z+n;
        setPos(z, y);
    }
    else
    {
        if (counterOfIterations == NUMBER_OF_ITERATIONS)
            finish();
        else if ((counter+1) == antGraph->number_of_edges)
        {
            counterOfIterations++;
            antGraph->pheromone_globalUpdate(antNumber);
            if (antGraph->ant[antNumber].calculate_pheromones() < bestAnt->calculate_pheromones())
                *bestAnt = antGraph->ant[antNumber]; 
            if (counterOfIterations != NUMBER_OF_ITERATIONS)
            {
                antGraph->ant[antNumber].resetTabu();
                antGraph->ant[antNumber].change_edge_randomly();
                antGraph->ant[antNumber].setWayWeight(0.0);
                antGraph->ant[antNumber].setNumberOfVerticesTraversed(1);
            }
            counter = 0;
            k = 0;
            n = 0;
            int z = antGraph->ant[antNumber].edge;
            setStartingPos(X[z][0], X[z][1]);
            inVerticeFlag = true;
        }
        else
        {
            antGraph->ant[antNumber].walk(antGraph);
            setStartingCoords(Epoint.x(), Epoint.y());
            int z = antGraph->ant[antNumber].edge;
            SetEndCoords(X[z][0], X[z][1]);

            antGraph->pheromone_localUpdate(counter, antNumber);
            k = (Epoint.y()-Spoint.y())/(Epoint.x()-Spoint.x());
            n = Spoint.y() - k*Spoint.x();
            counter++;
        }
    }
}

void AntSim::finish() 
{
	if (numberOfAntsFinished >= NUMBER_OF_ANTS)
	{
		return;
	}
    numberOfAntsFinished++;
    if (numberOfAntsFinished == NUMBER_OF_ANTS)
    {
        int firstVer, secondVer;
        secondVer = bestAnt->getTabu(0);
        for (int i = 0; i < antGraph->number_of_edges-1; i++)
        {
            for (int j = i+1; j < antGraph->number_of_edges; j++)
            {
				scene->removeItem(graphicsEdge[i][j]);
                //delete graphicsEdge[i][j];
                graphicsEdge[i][j] = nullptr;
                graphicsEdge[j][i] = nullptr;
            }
        }
        finalEdges = new Edge*[antGraph->number_of_edges];
        for (int i = 1; i < antGraph->number_of_edges; i++)
        {
            firstVer = secondVer;
            secondVer = bestAnt->getTabu(i);
            finalEdges[i-1] =  new Edge(graphicsNode[firstVer], graphicsNode[secondVer], true);
            scene->addItem(finalEdges[i-1]);
        }
        finalEdges[antGraph->number_of_edges-1] = new Edge(graphicsNode[bestAnt->getTabu(0)], graphicsNode[bestAnt->getTabu(antGraph->number_of_edges-1)], true);
        scene->addItem(finalEdges[antGraph->number_of_edges-1]);
        delete bestAnt;
		bestAnt = nullptr;
		for (int i = 0; i < antGraph->number_of_edges; i++)
			delete[] graphicsEdge[i];
		delete[] graphicsEdge;
		graphicsEdge = new Edge**[1];
		graphicsEdge[0] = finalEdges;
    }
    scene->removeItem(this);
    delete this;
}

bool AntSim::isFinishNode()
{
    QPointF location = this->pos();
    float distance = euclidean_distance(Epoint.x(), Epoint.y(), location.x(), location.y());
    if (distance < speed && inVerticeFlag == false)
    {
        setStartingCoords(Epoint.x(), Epoint.y());
        inVerticeFlag = true;
        return true;
    }
    else if (inVerticeFlag == true && distance > speed)
        inVerticeFlag = false;
    else if (distance < speed)
        return true;
    return false;
}

bool AntSim::isFinishNodeCheck()
{
    QPointF location = this->pos();
    float distance = euclidean_distance(Epoint.x(), Epoint.y(), location.x(), location.y());
    if (distance < speed && inVerticeFlag == false)
        return true;
    else
        return false;
}
