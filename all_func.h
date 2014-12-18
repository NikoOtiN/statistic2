#ifndef ALL_FUNC_H
#define ALL_FUNC_H
#include <QVector>
#include <chrono>
#include <random>
#include <math.h>
#include <QDebug>

struct calc_data{
    QVector<QVector<double>> matrix;
    QVector<double> x;
    QVector<double> y;
    int A;
    int B;
    double t_A;
    double t_B;
    double t_cr;
};


QVector<bool> U(QVector<double> dynamic_series);
QVector<bool> L(QVector<double> dynamic_series);
double sample_mean(QVector<double> X);
void print_v(QVector<bool> v);
double f(int n);
double l_const(int n);
double t_test_cr(int v, double level);
int A(bool u, bool l);
int B(bool u, bool l);
int Asum(QVector<bool> U, QVector<bool> L);
int Bsum(QVector<bool> U, QVector<bool> L);
double quantile(double level);
QVector<QVector<double> > createMatrix(int k, int n, double m, double g, QVector<double> trend_mean,
                                       QVector<double> trend_s);
QVector<double> create_sample(int size, double m, double g,int k);
calc_data do_cucl(int k, int n, double m, double g, QVector<double> trend_m, QVector<double> trend_s,
                  double level);


#endif // ALL_FUNC_H
