#ifndef MODEL_H
#define MODEL_H

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

extern int player;
extern int place;

class model : public QWidget
{
    Q_OBJECT
public:
    explicit model(QWidget *parent = nullptr);
//     void paintEvent(QPaintEvent*);

    //按钮
    QPushButton *playerleft,*playerright;
    QPushButton *placeleft,*placeright;
    QPushButton *playerPic,*placePic;
    QPushButton *choose;

     //void keyPressEvent(QKeyEvent *e);






signals:

private slots:
    void player_leftPush();
    void player_rightPush();
    void choose_Push();
    void place_leftPush();
    void place_rightPush();


};

#endif // MODEL_H
