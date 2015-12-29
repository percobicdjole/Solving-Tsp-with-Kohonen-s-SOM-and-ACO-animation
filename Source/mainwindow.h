#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int getNumberOfVertices() const
    {
        return number_of_vertices;
    }
    float** getX() const
    {
        return X;
    }
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int number_of_vertices;
    float** X;
    bool insertFlag;
};

#endif // MAINWINDOW_H
