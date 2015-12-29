#ifndef SOM_H
#define SOM_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <QGraphicsScene>
#include "node.h"
#include "edge.h"
#include "somanimation.h"

namespace Ui {
class Som;
}

class Som : public QDialog
{
    Q_OBJECT

public:
    explicit Som(float** x, const int number_of_vertices, QWidget *parent = 0);
    ~Som();
protected:
	void closeEvent(QCloseEvent *event)
	{
		delete this;
		event->accept();
	}
private:
    Ui::Som *ui;
    QGraphicsScene *scene;
    Node** graphicsNode;
    QTimer* timer;
    const int number_of_vertices;
    somAnimation* Anim;
};

#endif // SOM_H
