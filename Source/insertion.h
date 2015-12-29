#ifndef INSERTION_H
#define INSERTION_H

#include <QDialog>

namespace Ui {
class Insertion;
}

class Insertion : public QDialog
{
    Q_OBJECT

public:
    explicit Insertion(QWidget *parent = 0);
    ~Insertion();
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

private:
    int number_of_vertices;
    float** X;
    Ui::Insertion *ui;
};

#endif // INSERTION_H
