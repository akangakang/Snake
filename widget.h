#ifndef WIDGET_H
#define WIDGET_H


#include<QWidget>
#include<QIcon>
#include<QPalette>
#include<QBrush>
#include<QPixmap>
#include<QPushButton>
#include<QMessageBox>
#include "game.h"
#include "AI.h"
#include "doublegame.h"
#include <QApplication>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT


public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    QApplication *app;

    //按钮
    QPushButton *startPush;
   QPushButton *exitPush;
    QPushButton *instruction;//说明
    QPushButton *modelchoose;

    
    
    
    
    game *gamewindow;
    model *modelwindow;
    doublegame *doublegameWindow;

    AI *aiwindow;


    void dealAIback();


private slots:
    void M_startPush();
    void M_exitPush();
    void modelchoose_Push();
     void aichoose_Push();


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
