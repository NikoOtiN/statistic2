#include "mainwindow.h"
#include "ui_mainwindow.h"


QString text = "<p>1. Характеристики динамического ряда</p><p> A = %1 , B = %2</p>";
QString text2 = "<p>2. Проверка гипотезы об отсутсвии тредна средних.</p><p>t<sub>1</sub> = %1, \
                t<sub>cr</sub> = %2 </p>";
QString correct1 = "<p> t<sub>1</sub> &lt; t<sub>cr</sub> Гипотеза подтверждена, тренд отсутствует.";
QString uncorrect1 = "<p> t<sub>1</sub> &gt; t<sub>cr</sub> Гипотеза отвергнута, что говорит о наличии тренда средних.";
QString text3 = "<p>2. Проверка гипотезы об отсутствии тренда дисперсий.</p><p>t<sub>2</sub> = %1, \
                t<sub>cr</sub> = %2 </p>";
QString correct2 = "<p> t<sub>2</sub> &lt; t<sub>cr</sub> Гипотеза подтверждена, тренд отсутствует.";
QString uncorrect2 = "<p> t<sub>2</sub> &gt; t<sub>cr</sub> Гипотеза отвергнута, что говорит о наличии дисперсий.";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dd = new Dialog(this);
    mainTab = new QTabWidget(this);

    mainPlot = new QwtPlot(this);
    mainPlot->setTitle("Результы эксперимента");
    mainPlot->setAxisTitle(QwtPlot::xBottom,"Значения уровней");
    mainPlot->setAxisTitle(QwtPlot::yLeft,"Среднее значение");
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette( Qt::gray );
    canvas->setBorderRadius( 10 );
    mainPlot->setCanvas(canvas);
    legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    mainPlot->insertLegend(legend);
    QwtPlotLayout *plotLayout = mainPlot->plotLayout();
    plotLayout->setAlignCanvasToScales( true );
    mainPlot->setAutoReplot(true);

    enterDataAction = new QAction("Ввод данных",this);
    connect(enterDataAction,SIGNAL(triggered()),this,SLOT(showDialog()));
    connect(dd,SIGNAL(accepted()),this,SLOT(calculate()));
    menuBar()->addAction(enterDataAction);

    mainTab->addTab(mainPlot,"Визуализация данных");

    textEdit = new QTextEdit(this);
    mainTab->addTab(textEdit,"Результаты решения");



    setCentralWidget(mainTab);
}

void MainWindow::showDialog()
{
    dd->show();
}
void MainWindow::calculate()
{
    mainPlot->detachItems();
    dialog_data data = dd->getParam();
    calc_data res = do_cucl(data.count_level,data.n,data.expected,data.deviation,data.trend_mean,
                            data.trend_s,data.a);
    QVector<double> pointsY= res.y;
    QVector<double> pointsX = res.x;

    QwtPlotCurve *samples = new QwtPlotCurve();
    samples->setStyle(QwtPlotCurve::Dots);
    samples->setPen(Qt::yellow,3);
    samples->setSamples(pointsX,pointsY);
    samples->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    samples->attach(mainPlot);
    textEdit->clear();
    populate(res);
}

void MainWindow::populate(calc_data data)
{
    textEdit->append(text.arg(QString::number(data.A),QString::number(data.B)));
    textEdit->append(text2.arg(QString::number(data.t_A),QString::number(data.t_cr)));
    if(data.t_A<data.t_cr)
    {
        textEdit->append(correct1);
    }else{
        textEdit->append(uncorrect1);
    }
    textEdit->append(text3.arg(QString::number(data.t_B),QString::number(data.t_cr)));
    if(data.t_B<data.t_cr)
    {
        textEdit->append(correct2);
    }else{
        textEdit->append(uncorrect2);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
