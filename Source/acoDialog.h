#ifndef ACO_H
#define ACO_H

#include <QDialog>
#include <QtCore>
#include <QTimer>
#include <QtWidgets>
#include <QCloseEvent>
#include <QKeyEvent>
#include "PheromoneGraph.h"
#include "node.h"
#include "antsim.h"

namespace Ui {
class Aco;
}

class Aco : public QDialog
{
    Q_OBJECT

public:
    explicit Aco(float** x, const int number_of_vertices, QWidget *parent = 0);
    ~Aco();
protected:
	void closeEvent(QCloseEvent *event)
	{
		delete this;
		//event->accept();
	}
private:
    Ui::Aco *ui;
    QGraphicsScene *scene;
    Node** graphicsNode;
    Edge*** graphicsEdge;
    QTimer* timer;
    PheromoneGraph* antGraph;
    AntSim** antsSim;
};

#endif // ACO_H
