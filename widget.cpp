#include "widget.h"
#include"game.h"
#include"model.h"
#include<QDebug>


int player=1;
int place=1;
extern int player;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1400,660);
    this->setWindowTitle("阿钪的全世界最可爱的贪吃蛇");
    this->setWindowIcon(QIcon(":/new/prefix1/image/MiaoMenXiao.PNG"));
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/image/cover.png").scaled(this->size())));

    this->setPalette(palette);


    //设置按钮
    startPush=new QPushButton(this);
    startPush->setIconSize(QSize(250,250));
    startPush->setGeometry(540,410,160,80);    //  改响应范围
    startPush->setIcon(QIcon(":/new/prefix1/image/START.png"));
    startPush->setFlat(1);


    exitPush=new QPushButton(this);
    exitPush->setIconSize(QSize(250,250));
    exitPush->setGeometry(545,490,160,80);
    exitPush->setIcon(QIcon(":/new/prefix1/image/exit1.png"));
    exitPush->setFlat(1);//设置按钮的透明属性
  // exitBox=new QMessageBox;
   // connect(exitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));



    instruction=new QPushButton(this);
    instruction->setIconSize(QSize(250,250));
    instruction->setGeometry(700,410,160,80);
    instruction->setIcon(QIcon(":/new/prefix1/image/AI.png"));
    instruction->setFlat(1);


    connect(instruction,SIGNAL(clicked(bool)),this,SLOT(aichoose_Push()));



//    connect(aiwindow,&AI::backSignals,this,&Widget::dealAIback);

    modelchoose=new QPushButton(this);
    modelchoose->setIconSize(QSize(250,250));
    modelchoose->setGeometry(700,492,160,80);
    modelchoose->setIcon(QIcon(":/new/prefix1/image/model.png"));
    modelchoose->setFlat(1);



    connect(startPush,SIGNAL(clicked(bool)),this,SLOT(M_startPush()));
    connect(modelchoose,SIGNAL(clicked(bool)),this,SLOT(modelchoose_Push()));
    connect(exitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));




}

void Widget::dealAIback()
{
    this->show();
    aiwindow->close();
}

void Widget::aichoose_Push()
{

    aiwindow=new AI;

    aiwindow->show();
   // this->hide();

}

void Widget::M_startPush()
{

    if(player==1)
    {
        gamewindow=new game(this);  //创建一个新的界面，任然以原来的界面为父窗口，退出后可以直接回到上一个界面。
        gamewindow->show();

    }

    if(player==2)
    {
        doublegameWindow=new doublegame(this);
        doublegameWindow->show();
    }


}


void Widget::M_exitPush()
{

    //this->close();
   app->exit();

}

void Widget::modelchoose_Push()
{
    modelwindow =new model(this);
    modelwindow->show();
}



Widget::~Widget()
{
    delete this;
}

