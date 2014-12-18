#include <qDebug>
#include "all_func.h"

//Выброчное среднее
double sample_mean(QVector<double> X)
{
    double sum=0;
    if(X.empty())
    {
        //throw length_error("sample_mean: error empty vector!");
    }
    for(auto i : X)
    {
        sum+=i;
    }
    return sum/X.size();
}

calc_data do_cucl(int k, int n, double m, double g, QVector<double> trend_m, QVector<double> trend_s,
                  double level)
{
    QVector<QVector<double>> matrix = createMatrix(k,n,m,g,trend_m,trend_s);
    QVector<double> y;
    for(auto sample : matrix)
    {
        y.push_back(sample_mean(sample));
    }
    QVector<double> x;
    for(int i = 0; i<k;i++)
    {
        x.push_back(i);
    }

    QVector<bool> u = U(y);
    QVector<bool> l = L(y);

    int a = Asum(u,l);
    int b = Bsum(u,l);

    //Тренд средних
    double F = f(k);
    double t_stat_mean = a/F;

    double L = l_const(k);
    double t_stat_s = (b-F*F)/L;
    double t_cr = t_test_cr(k,level);
    qDebug() << "a" << a;
    qDebug() << "b" << b;
    qDebug() << "t mean" << t_stat_mean;
    qDebug() << "t s" << t_stat_s;
    qDebug() << t_cr;
    calc_data data;
    data.x=x;
    data.y=y;
    data.t_A=t_stat_mean;
    data.t_B=t_stat_s;
    data.t_cr=t_cr;
    data.A=a;
    data.B=b;
    return data;
}

double t_test_cr(int v, double level)
{
    double u = quantile(1-level/2);
    double q1 = (u*u+1)*u/4;
    double q2 = ((5*u*u+16)*pow(u,2) + 3)*u/96;
    double q3 = (((3*u*u+19)*u*u+17)*u*u-15)*u/384;
    double q4 = ((((79*u*u+776)*u*u + 1482)*u*u -1920)*u*u-945)*u/92160;
    double t = u + q1/v + q2/pow(v,2) + q3/pow(v,3) + q4/pow(v,4);
    return t;
}

//Расчет квантили норм. распределения.
double quantile(double level)
{
   double q, t;
   double one = 1;

   t = level < 0.5 ? level : one - level;
   t = sqrt(-2 * log(t));
   q = t - ((0.010328 * t + 0.802853) * t + 2.515517) /
      (((0.001308 * t + 0.189269) * t + 1.432788) * t + 1);
   return level > 0.5 ? q : -q;
}


double f(int n)
{
    return sqrt(2*log(n)-0.8456);
}

double l_const(int n)
{
    return sqrt(2*log(n)-3.4253);
}

QVector<bool> U(QVector<double> dynamic_series)
{
    QVector<bool> u;
    for(int i = 1; i < dynamic_series.size(); i++)
    {
        bool result=false;
        int j = i - 1;
        do{
          result = dynamic_series[ j ] < dynamic_series[ i ];
          j--;
        }while(( j>=0 )&&( result ));
        u.push_back(result);
    }
    return u;
}

QVector<bool> L(QVector<double> dynamic_series)
{
    QVector<bool> u;
    for(int i = 1; i < dynamic_series.size(); i++)
    {
        bool result=false;
        int j = i - 1;
        do{
          result = dynamic_series[ j ] > dynamic_series[ i ];
          j--;
        }while(( j>=0 )&&( result ));
        u.push_back(result);
    }
    return u;
}

int A(bool u, bool l)
{
    return u-l;
}

int B(bool u,bool l)
{
    return u+l;
}

int Asum(QVector<bool> U, QVector<bool> L)
{
    int sum = 0;
    auto l = L.begin();
    for(auto u :U)
    {
        sum += A(u,*l);
        l++;
    }
    return sum;
}

int Bsum(QVector<bool> U, QVector<bool> L)
{
    int sum = 0;
    auto l = L.begin();
    for(auto u :U)
    {
        sum += B(u,*l);
        l++;
    }
    return sum;
}

QVector<QVector<double> > createMatrix(int k, int n, double m, double g, QVector<double> trend_mean,
                                       QVector<double> trend_s)
{
    QVector<QVector<double> > matrix;
    if((trend_mean.size()!=2)||(trend_s.size()!=2))
    {
        qDebug() << "uncorrect number trend parametr";
        return matrix;
    }

    double mi, gi;
    for(int i = 0; i<k; i++)
    {
        mi = m + trend_mean[0]*i + trend_mean[1]*i*i;
        gi = g + trend_s[0]*i + trend_s[1]*i*i;
        matrix.push_back(create_sample(n,mi,gi,i));
    }
    return matrix;
}

QVector<double> create_sample(int size, double m, double g,int k)
{
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count()*k;
    std::default_random_engine generator(seed1);
    std::normal_distribution<double> distribution(m,g);
    QVector<double> tmp;
    for(int i = 0; i <size; i++)
    {
        tmp.push_back(distribution(generator));
    }
    return tmp;
}


void print_v(QVector<bool> v)
{
    for(auto e : v)
    {
        qDebug() << e;
    }
}
