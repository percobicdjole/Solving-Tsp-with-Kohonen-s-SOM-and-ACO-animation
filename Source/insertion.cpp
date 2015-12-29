#include "insertion.h"
#include "ui_insertion.h"
#include <iostream>
#include "coordinatedialog.h"

Insertion::Insertion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insertion)
{
    ui->setupUi(this);
}

Insertion::~Insertion()
{
    delete ui;
}

void Insertion::on_pushButton_clicked()
{
    number_of_vertices = ui->lineEdit->text().toInt();
    if (number_of_vertices < 1 || number_of_vertices > 300)
    {
        ui->lineEdit->clear();
        return; // ISPISI
    }
    X = new float*[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++)
            X[i] = new float[2];

    if (ui->checkBox->isChecked())
    {
        CoordinateDialog* mCoordinateDialog = new CoordinateDialog(number_of_vertices);
        mCoordinateDialog->setWindowTitle("Insert coordinates");
        mCoordinateDialog->setModal(true);
        mCoordinateDialog->exec();
        X = mCoordinateDialog->getX();
    }
    else
    {
        for (int i = 0; i < number_of_vertices; i++)
        {
             X[i][0] = qrand()/(double)RAND_MAX * 900;
             X[i][1] = qrand()/(double)RAND_MAX * 900;
        }
    }
    this->close();
}
