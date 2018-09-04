#include "widget.h"
#include "ui_widget.h"
#include <time.h>
#include <QString>
#include <QThread>

Ui::Widget *P_ui; //UI widget 주소를 저장하는 전역변수

void delay(clock_t n)
{
  clock_t start = clock();
  while(clock() - start < n);
}

const QString currentDateTime() {  //시간 불러오는 함수
    time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

    return buf;
}


class Thread : public QThread { //쓰래드 클래스
protected:
 void run() {
     while(1){
        P_ui->TimeLabel->setText(currentDateTime());
        delay(1000);
     }
 }
};

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) //생성자
{
    ui->setupUi(this);
    P_ui = ui; //ui주소를 전역으로 지정


    ui->TimeLabel->setStyleSheet("background:rgb(0,0,0);color : rgb(255,255,255)"); //배경, 글자색 지정

    Thread *t = new Thread;//쓰래드 생성
    t->start(); //쓰래드 시작 분기
}



void Widget::ShowTime(){ //안쓰는함수 - 현재시간이랑 동기화
     ui->TimeLabel->setText(currentDateTime());
}


Widget::~Widget() //소멸자
{
    delete ui;
}


