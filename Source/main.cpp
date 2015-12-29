#include "mainwindow.h"
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    srand(time(NULL));
    qsrand(time(NULL));
    w.setWindowTitle("Travelling salesman problem");
    w.show();

    return a.exec();
}
