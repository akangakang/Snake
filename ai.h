#ifndef AI_H
#define AI_H

#include <QWidget>
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


class AI : public QWidget
{
    Q_OBJECT
public:
    explicit AI(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
  //  void keyPressEvent(QKeyEvent *e);


    struct cube
    {
        int x,y,step;
        cube() { step = 0; }
        cube(int _x, int _y, int _step = 0)
        {
                x = _x;
                y = _y;
                step = _step;
        }
        bool operator==(const cube  &t)const {
             return (x == t.x) && (y == t.y);
          }
       bool operator!=(const cube &t)const {
                return (x != t.x) || (y != t.y);
            }



    };

    //蛇的移动
    int moveFlage =1;
    void addTopRectF();
    void addDownRectF();
    void addLeftRectF();
    void addRightRectF();
    void deleteLastRectF();
    bool snakeStrike();
    bool snakeOut();


    //贪吃蛇本体
    QList<cube> snake;


    int snakeNodeWidth = 20;
    int snakeNodeHeight = 20;
    int againNum=0;

    //食物
    bool gameOver = false;
    bool gameStart = false;

    //普通食物
   // QList<QRectF> rewardNode;
    cube food;

    //时间设置
    QTimer *timer;
     int time = 50;

    //控制游戏结束
    bool finish=false;
    bool gameIsOver=false;

    //回去信号
    void sendGOBackSignals();

    //有关ai
   // int getNextCmd();
    //int canFindPath(const cube &start, const cube &end);
    /*bool canFindTail(cube start);
    bool canFindFood(cube start);
    int nextCmdToFood();
    int nextCmdTOFarAway(const cube &start);
    bool onSnake_ExceptTail(cube start);
    int nextCmdTOTail();
    int getManhattanDistance(cube a,cube b);
*/
private:
    QPushButton *goBack;
    //QPushButton *start;
  //  QPushButton *stop;

    QPalette *palette;

signals:
    void backSignals();

public slots:
      void timeOut();
};

#endif // AI_H
