#include "acoDialog.h"
#include "ui_aco.h"
#include "edge.h"
#include "node.h"
#include "ant.h"

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QLayout>
#include <math.h>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <iostream>

class GAlok
{
public:
	GAlok() { std::cout << "Greska u alokaciji" << std::endl; }
};

using namespace heuristic_constants;

Aco::Aco(float** x, const int number_of_vertices, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aco)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
	if (scene == nullptr)
		throw GAlok();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 996, 940);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    //ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);      // Da ne nalazi precizne updateove lokacije
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); // Pravi grafiku brzom
    ui->graphicsView->scale(qreal(0.8), qreal(0.8));
    ui->graphicsView->setMinimumSize(400, 400);

    QPen blackPen(Qt::black);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine, blackPen);
    scene->addLine(LeftLine, blackPen);
    scene->addLine(RightLine, blackPen);
    scene->addLine(BottomLine, blackPen);

	graphicsNode = new Node*[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++)
    {
        graphicsNode[i] = new Node(false);
		if (graphicsNode[i] == nullptr)
			throw GAlok();
        scene->addItem(graphicsNode[i]);
        graphicsNode[i]->setPos(x[i][0], x[i][1]);
    }

    graphicsEdge = new Edge**[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++)
        graphicsEdge[i] = new Edge*[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++)
    {
        graphicsEdge[i][i] = nullptr;
        for (int j = i+1; j < number_of_vertices; j++)
        {
            graphicsEdge[i][j] =  new Edge(graphicsNode[i], graphicsNode[j], false);
			if (graphicsEdge[i][j] == nullptr)
				throw GAlok();
            graphicsEdge[j][i] = graphicsEdge[i][j];
            scene->addItem(graphicsEdge[i][j]);
        }
    }

    antGraph = new PheromoneGraph(number_of_vertices, x);
	if (antGraph == nullptr)
		throw GAlok();
    Ant* bestAnt = new Ant;
	if (bestAnt == nullptr)
		throw GAlok();
    bestAnt->setWayWeight(INFINITI);
    AntSim::antGraph = antGraph;
    AntSim::X = x;
    AntSim::bestAnt = bestAnt;
    AntSim::graphicsNode = graphicsNode;
    AntSim::finalEdges = nullptr;
	AntSim::numberOfAntsFinished = 0;
    antsSim = new AntSim*[NUMBER_OF_ANTS];
    for (int i = 0; i < NUMBER_OF_ANTS; i++)
    {
        antsSim[i] = new AntSim(i, scene, graphicsEdge);
		if (antsSim[i] == nullptr)
			throw GAlok();
        scene->addItem(antsSim[i]);
    }
    timer = new QTimer(this);
	if (timer == nullptr)
		throw GAlok();
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(0);
}

Aco::~Aco()
{
	for (int i = 0; i < antGraph->number_of_edges; i++)
	{
		scene->removeItem(graphicsEdge[0][i]);
		delete graphicsEdge[0][i];
	}
    for (int i = 0; i < antGraph->number_of_edges; i++)
        delete graphicsNode[i];
	for (int i = 0; i < NUMBER_OF_ANTS; i++)
		antsSim[i] = nullptr;
    delete antGraph;
	antGraph = nullptr;
    delete[] graphicsEdge;
	graphicsEdge = nullptr;
    delete[] graphicsNode;
	graphicsNode = nullptr;
	delete[] antsSim;
	antsSim = nullptr;
	disconnect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    delete timer;
	timer = nullptr;
	scene->clear();
    delete scene;
	scene = nullptr;
    delete ui;
}
