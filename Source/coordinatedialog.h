#ifndef COORDINATEDIALOG_H
#define COORDINATEDIALOG_H

#include <QDialog>

namespace Ui {
class CoordinateDialog;
}

class CoordinateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CoordinateDialog(const int n, QWidget *parent = 0);
    ~CoordinateDialog();
    float** getX() const
    {
        return X;
    }

private slots:
    void on_pushButton_clicked();

private:
    Ui::CoordinateDialog *ui;
    int n;
    int k;
    float** X;
};

#endif // COORDINATEDIALOG_H
