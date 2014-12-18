#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

struct dialog_data{
    double expected;
    double deviation;
    QVector<double> trend_mean;
    QVector<double> trend_s;
    double count_level;
    double n;
    double a;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    dialog_data getParam();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
