#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->TimeLabel->setText("Hello,World");
}

Widget::~Widget()
{
    delete ui;
}
