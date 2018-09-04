#include "widget.h"
#include "ui_widget.h"
#include <time.h>
#include <QString>
#include <QThread>

Ui::Widget *P_ui;

void delay(clock_t n)
{
  clock_t start = clock();
  while(clock() - start < n);
}

const QString currentDateTime() {
    time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

    return buf;
}


class Thread : public QThread {
protected:
 void run() {
     while(1){
        P_ui->TimeLabel->setText(currentDateTime());
        delay(1000);
     }
 }
};

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    P_ui = ui;
    Thread *t = new Thread;

    t->start();
}



void Widget::ShowTime(){
     ui->TimeLabel->setText(currentDateTime());
}


Widget::~Widget()
{
    delete ui;
}


