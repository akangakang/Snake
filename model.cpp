#include "model.h"
#include "game.h"
#include "widget.h"


model::model(QWidget *parent) : QWidget(parent)
{
    //使键盘响应
    this->grabKeyboard();

    //界面控制
    this->setAutoFillBackground(true);//设置父窗口背景可被覆盖填充
    this->resize(1400,660);
    this->setWindowTitle("阿钪的全世界的最可爱的贪吃蛇");
    this->setWindowIcon(QIcon(":/new/prefix1/image/MiaoMen.PNG"));

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/image/modelbacknew.png").scaled(this->size())));
    this->setPalette(palette);

    //========================================按钮============================================================//

    switch(player){
    case 1:
        playerPic=new QPushButton(this);
        playerPic->setIconSize(QSize(400,400));
        playerPic->setGeometry(233,86,400,400);
        playerPic->setIcon(QIcon(":/new/prefix1/image/singlepurple.png"));
        playerPic->setFlat(1);

        placePic=new QPushButton(this);
        placePic->setIconSize(QSize(400,400));
        placePic->setGeometry(840,80,400,400);
        break;

    case 2:
        playerPic=new QPushButton(this);
        playerPic->setIconSize(QSize(400,400));
        playerPic->setGeometry(233,86,400,400);
        playerPic->setIcon(QIcon(":/new/prefix1/image/doublepurple.png"));
        playerPic->setFlat(1);

        placePic=new QPushButton(this);
        placePic->setIconSize(QSize(400,400));
        placePic->setGeometry(840,80,400,400);
    }



    switch(place){

    case 1:
        placePic->setIcon(QIcon(":/new/prefix1/image/MiaoMenXiao.PNG"));
        break;
    case 2:
        placePic->setIcon(QIcon(":/new/prefix1/image/SanCanXiao.png"));
        break;
    case 3:
        placePic->setIcon(QIcon(":/new/prefix1/image/ShiNanXiao.png"));
        break;
    case 4:
        placePic->setIcon(QIcon(":/new/prefix1/image/TuoXieXiao.png"));
        break;
    }


    placePic->setFlat(1);

    choose=new QPushButton(this);
    choose->setIconSize(QSize(400,200));
    choose->setGeometry(660,520,160,50);
    choose->setIcon(QIcon(":/new/prefix1/image/choose.png"));
    choose->setFlat(1);



    playerleft=new QPushButton(this);
    playerleft->setIconSize(QSize(180,380));
    playerleft->setGeometry(160,220,60,160);
    playerleft->setIcon(QIcon(":/new/prefix1/image/left.png"));
    playerleft->setFlat(1);

    playerright=new QPushButton(this);
    playerright->setIconSize(QSize(180,380));
    playerright->setGeometry(630,220,60,160);
    playerright->setIcon(QIcon(":/new/prefix1/image/right.png"));
    playerright->setFlat(1);

    placeleft=new QPushButton(this);
    placeleft->setIconSize(QSize(180,380));
    placeleft->setGeometry(775,220,60,160);
    placeleft->setIcon(QIcon(":/new/prefix1/image/left.png"));
    placeleft->setFlat(1);

    placeright=new QPushButton(this);
    placeright->setIconSize(QSize(180,380));
    placeright->setGeometry(1240,220,60,160);
    placeright->setIcon(QIcon(":/new/prefix1/image/right.png"));
    placeright->setFlat(1);




    connect(playerleft,SIGNAL(clicked(bool)),this,SLOT(player_leftPush()));
    connect(playerright,SIGNAL(clicked(bool)),this,SLOT(player_rightPush()));
    connect(choose,SIGNAL(clicked(bool)),this,SLOT(choose_Push()));
    connect(placeleft,SIGNAL(clicked(bool)),this,SLOT(place_leftPush()));
    connect(placeright,SIGNAL(clicked(bool)),this,SLOT(place_rightPush()));
}

void model::player_leftPush()
{
    if(player==1) return;
    player--;
    playerPic->setIcon(QIcon(":/new/prefix1/image/singlepurple.png"));

}

void model::player_rightPush()
{
    if(player==2) return;
    player++;
    playerPic->setIcon(QIcon(":/new/prefix1/image/doublepurple.png"));
}

void model::place_leftPush()
{
    if(place==1) return;
    place--;
    switch(place){

    case 1:
        placePic->setIcon(QIcon(":/new/prefix1/image/MiaoMenXiao.PNG"));
        break;
    case 2:
        placePic->setIcon(QIcon(":/new/prefix1/image/SanCanXiao.png"));
        break;
    case 3:
        placePic->setIcon(QIcon(":/new/prefix1/image/ShiNanXiao.png"));
        break;
    case 4:
        placePic->setIcon(QIcon(":/new/prefix1/image/TuoXieXiao.png"));
        break;
    }


}
void model::place_rightPush()
{
    if(place==4)return;
    place++;
    switch(place){

    case 1:
        placePic->setIcon(QIcon(":/new/prefix1/image/MiaoMenXiao.PNG"));
        break;
    case 2:
        placePic->setIcon(QIcon(":/new/prefix1/image/SanCanXiao.png"));
        break;
    case 3:
        placePic->setIcon(QIcon(":/new/prefix1/image/ShiNanXiao.png"));
        break;
    case 4:
        placePic->setIcon(QIcon(":/new/prefix1/image/TuoXieXiao.png"));
        break;
    }

}
void model::choose_Push()
{
    this->close();

}
