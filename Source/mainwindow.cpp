#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "insertion.h"
#include "acoDialog.h"
#include "somDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    X = nullptr;
    number_of_vertices = 0;
    insertFlag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (insertFlag == false)
        insertFlag = true;
    if (X != nullptr)
    {
        delete[] X;
        X = nullptr;
    }
    Insertion* mInsertion = new Insertion;
    mInsertion->setWindowTitle("Insert number of vertices");
    mInsertion->setModal(true);
    mInsertion->exec();
    number_of_vertices = mInsertion->getNumberOfVertices();
    X = mInsertion->getX();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (insertFlag == false)
        return;
    Aco* mAco = new Aco(X, number_of_vertices);
    mAco->setWindowTitle("Ant colony optimization");
    mAco->setModal(true);
    mAco->exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    if (insertFlag == false)
        return;
    Som* mSom = new Som(X, number_of_vertices);
    mSom->setWindowTitle("Kohonens's self organizing networks");
    mSom->setModal(true);
    mSom->exec();
}
