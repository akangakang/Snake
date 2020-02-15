#ifndef GAME_H
#define GAME_H

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
#include<model.h>






class game : public QWidget
{
    Q_OBJECT
public:
    explicit game(QWidget *parent = nullptr);
     void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *e);



    //按钮
   // QPushButton *playerChoose;
    //QPushButton *placeChoose;
    QPushButton *exitPush;
   // QPushButton *againPush;

    game *gamewindow;





public:



    //蛇的移动
    int moveFlage =1;
    void addTopRectF();
    void addDownRectF();
    void addLeftRectF();
    void addRightRectF();
    void deleteLastRectF();
    bool snakeStrike();
    bool snakeOut();



private slots:
  //  void M_againPush();
    void M_exitPush();

public:

       //贪吃蛇本体
       QList<QRectF> snake;


       int snakeNodeWidth = 20;
       int snakeNodeHeight = 20;
      // int againNum=0;



       //食物
       bool gameOver = false;
       bool gameStart = false;

       //普通食物
       QList<QRectF> rewardNode;
      // 长两节食物
       QList<QRectF>  doubleRewardNode;
       //减一截食物
       QList<QRectF> lessNode;




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


       //有关传送门
       QRectF left;
       QRectF right;
       QRectF center;



public slots:
       //void move();
    void timeOut();
    void rewardTimeOut();
    void barrierTimeOut();


private:
    QPalette *palette;


};

#endif // GAME_H
