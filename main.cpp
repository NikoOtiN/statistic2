#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <all_func.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QVector<double> v;
    v.push_back(4);
    v.push_back(3);
    v.push_back(6);
    v.push_back(1);
    QVector<bool> u = U(v);
    QVector<bool> l = L(v);
    print_v(u);
    print_v(l);
    qDebug() << Asum(u,l);
    qDebug() << Bsum(u,l);


    w.show();

    return a.exec();
}
