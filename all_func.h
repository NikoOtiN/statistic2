#ifndef ALL_FUNC_H
#define ALL_FUNC_H
#include <QVector>

QVector<bool> U(QVector<double> dynamic_series);
QVector<bool> L(QVector<double> dynamic_series);
double sample_mean(QVector<double> X);
void print_v(QVector<bool> v);
int A(bool u, bool l);
int B(bool u, bool l);
int Asum(QVector<bool> U, QVector<bool> L);
int Bsum(QVector<bool> U, QVector<bool> L);

void test();



#endif // ALL_FUNC_H
