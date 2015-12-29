#include "somDialog.h"
#include "ui_som.h"

#include "edge.h"
#include "node.h"
#include "KohonenNetwork.h"

#include <QWidget>
#include <QTime>
#include <QLayout>
#include <math.h>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QWidget>

Som::Som(float** x, const int number_of_vertices, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Som),
    number_of_vertices(number_of_vertices)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 1000, 1000);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); // Pravi grafiku brzom
    ui->graphicsView->scale(qreal(0.8), qreal(0.8));
    ui->graphicsView->setMinimumSize(400, 400);

    QPen whitePen(Qt::white);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine, whitePen);
    scene->addLine(LeftLine, whitePen);
    scene->addLine(RightLine, whitePen);
    scene->addLine(BottomLine, whitePen);

    graphicsNode = new Node*[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++)
    {
        graphicsNode[i] = new Node(false);
        scene->addItem(graphicsNode[i]);
        graphicsNode[i]->setPos(x[i][0], x[i][1]);
    }

    Anim = new somAnimation(number_of_vertices, x, scene);
    scene->addItem(Anim);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(0);
}

Som::~Som()
{
    for (int i = 0; i < number_of_vertices; i++)
        delete graphicsNode[i];
    delete[] graphicsNode;
	graphicsNode = nullptr;
	scene->removeItem(Anim);
    delete Anim;
	Anim = nullptr;
	disconnect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
	delete timer;
	timer = nullptr;
	scene->clear();
	delete scene;
	scene = nullptr;
    delete ui;
}
