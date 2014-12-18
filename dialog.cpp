#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(accept()));
}

dialog_data Dialog::getParam()
{
    dialog_data tmp;
    tmp.expected=ui->expected_sb->value();
    tmp.deviation=ui->deviation_sb->value();
    tmp.a = ui->level_sb->value();
    tmp.count_level=ui->count_level->value();
    tmp.n = ui->size_n->value();
    QVector<double> trend_m;
    trend_m.push_back(ui->trend_mean_SB1->value());
    trend_m.push_back(ui->trend_mean_SB2->value());
    QVector<double> trend_s;
    trend_s.push_back(ui->trend_s_SB1->value());
    trend_s.push_back(ui->trend_s_SB2->value());
    tmp.trend_mean=trend_m;
    tmp.trend_s=trend_s;
    return tmp;
}

Dialog::~Dialog()
{
    delete ui;
}
