#include <qDebug>

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

QVector<bool> u(QVector<double> dynamic_series)
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

QVector<bool> l(QVector<double> dynamic_series)
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

void test()
{
    qDebug() << A(0,0);
    qDebug() << A(1,1);
  qDebug() << A(0,1);
}

void print_v(QVector<bool> v)
{
    for(auto e : v)
    {
        qDebug() << e;
    }
}
