#ifndef DOUBLEGAME_H
#define DOUBLEGAME_H

#include <QWidget>
#include<QIcon>
#include<QPalette>
#include<QBrush>
#include<QPixmap>
#include<QPushButton>
#include<QMessageBox>
#include<QPaintEvent>
#include<QPainter>
#include<QLabel>
#include<QTimer>
#include<QTime>
#include<ctime>
#include<QButtonGroup>
#include<QKeyEvent>
class doublegame : public QWidget
{
    Q_OBJECT
public:
    explicit doublegame(QWidget *parent = nullptr);
     void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *e);


    //按钮
   // QPushButton *playerChoose;
    //QPushButton *placeChoose;
    QPushButton *exitPush;
  //  QPushButton *againPush;

    doublegame *doublegamewindow;


public:


    //蛇的移动
    int moveFlage1 =1;
    void addTopRectF1();
    void addDownRectF1();
    void addLeftRectF1();
    void addRightRectF1();
    void deleteLastRectF();
    bool snakeStrike();
    bool snakeOut();

    int moveFlage2 =1;
    void addTopRectF2();
    void addDownRectF2();
    void addLeftRectF2();
    void addRightRectF2();
    void deleteLastRectF2();



private slots:
   // void M_againPush();
    void M_exitPush();

public:

       //贪吃蛇本体
       QList<QRectF> snake1;
       QList<QRectF> snake2;


       int snakeNodeWidth = 20;
       int snakeNodeHeight = 20;

       //奖励节点
       bool gameOver = false;
       bool gameStart = false;
       QList<QRectF> rewardNode;
      // QRectF food;



       //生成障碍物
       QList<QRectF> barrier;


       //时间设置
       QTimer *timer;
       QTimer *rewardTimer;
       QTimer *barrierTimer;
       int time = 100;





       //控制游戏结束
       bool finish=false;
       bool gameIsOver=false;
       int winner;


public slots:
       //void move();
    void timeOut();
    void rewardTimeOut();
    void barrierTimeOut();


private:
    QPalette *palette;
};

#endif // DOUBLEGAME_H
