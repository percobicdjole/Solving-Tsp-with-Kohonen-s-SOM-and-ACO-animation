#include "coordinatedialog.h"
#include "ui_coordinatedialog.h"
#include <iostream>

CoordinateDialog::CoordinateDialog(const int n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoordinateDialog),
    n(n)
{
    ui->setupUi(this);
    k = 0;
    X = new float*[n];
    for (int i = 0; i < n; i++)
        X[i] = new float[2];
    ui->tableWidget->setRowCount(n);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

CoordinateDialog::~CoordinateDialog()
{
    delete ui;
}

void CoordinateDialog::on_pushButton_clicked()
{
    X[k][0] = ui->lineEdit->text().toFloat();
    if (X[k][0] < 1 || X[k][0] > 900)
    {
        ui->lineEdit->clear();
        return;
    }
    X[k][1] = ui->lineEdit_2->text().toFloat();
    if (X[k][1] < 1 || X[k][1] > 900)
    {
        ui->lineEdit_2->clear();
        return;
    }
    ui->tableWidget->setItem(k, 0, new QTableWidgetItem(ui->lineEdit->text()));
    ui->tableWidget->setItem(k, 1, new QTableWidgetItem(ui->lineEdit_2->text()));
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    k++;
    if (k == n)
        this->close();
}

