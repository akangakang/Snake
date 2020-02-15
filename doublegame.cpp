#include "doublegame.h"
#include "model.h"
#include "widget.h"

extern int place;
extern int player;

doublegame::doublegame(QWidget *parent) : QWidget(parent)
{
    //使键盘响应
    this->grabKeyboard();


    //界面控制
    this->setAutoFillBackground(true);//设置父窗口背景可被覆盖填充
    this->resize(1400,660);
    this->setWindowTitle("阿钪的全世界的最可爱的贪吃蛇");



    this->setWindowIcon(QIcon(":/new/prefix1/image/庙门.PNG"));

    QPalette palette;
    switch(place){

    case 1:
        palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/image/MiaoMen.PNG").scaled(this->size())));
        break;
    case 2:
        palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/image/SanCan.jpg").scaled(this->size())));
        break;
    case 3:
        palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/image/ShiNan.png").scaled(this->size())));
        break;
    case 4:
        palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/image/TuoXie.png").scaled(this->size())));
        break;
    }


    this->setPalette(palette);

     qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

     //生成初始的蛇
        //   snake.append(QRectF(QRectF(qrand()%(this->width()/20)*20,qrand()%(this->height()/20)*20,snakeNodeWidth,snakeNodeHeight)));
        snake1.append(QRectF(snakeNodeWidth*30,snakeNodeHeight*15,snakeNodeWidth,snakeNodeHeight));
        addTopRectF1();
        addTopRectF1();
        snake2.append(QRectF(snakeNodeWidth*35,snakeNodeHeight*15,snakeNodeWidth,snakeNodeHeight));
        addTopRectF2();
        addTopRectF2();

        //首先生成一个奖励节点
        rewardNode.append(QRectF(qrand()%(this->width()/20)*20,qrand()%(this->height()/20)*20,snakeNodeWidth,snakeNodeWidth));



        //生成初始地形

        for(int j=0;j<4;j++)
        {
            barrier.append(QRectF(qrand()%(this->width()/20)*20,qrand()%(this->height()/20)*20,snakeNodeWidth,snakeNodeWidth));
            for(int i=0;i<10;i++)
            {
                int dir=qrand()%2;
                switch (dir) {
                case 0:
                    //向右
                    barrier.append(QRectF(barrier.at(barrier.length()-1).x()+snakeNodeWidth,barrier.at(barrier.length()-1).y(),snakeNodeWidth,snakeNodeHeight));
                    break;
                case 1:
                    //向下
                     barrier.append(QRectF(barrier.at(barrier.length()-1).x(),barrier.at(barrier.length()-1).y()-snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
                    break;
                }
            }


        }





        //设置刷新时间
        timer = new QTimer;
        connect(timer, SIGNAL(timeout()),this,SLOT(timeOut()));
        timer->start(time);

        rewardTimer = new QTimer;
        connect(rewardTimer,SIGNAL(timeout()),this,SLOT(rewardTimeOut()));
        rewardTimer->start(time*10);

        barrierTimer= new QTimer;
        connect(barrierTimer,SIGNAL(timeout()),this,SLOT(barrierTimeOut()));
        barrierTimer->start(time*100);


        //设置按钮
       // againPush=new QPushButton(this);
        exitPush=new QPushButton(this);

        /*againPush->setIconSize(QSize(0,0));
        againPush->setGeometry(0,0,0,0);
        againPush->setIcon(QIcon(":/new/prefix1/image/AGAIN.png"));
        againPush->setFlat(1);*/
        exitPush->setIconSize(QSize(0,0));
        exitPush->setGeometry(0,0,0,0);
        exitPush->setIcon(QIcon(":/new/prefix1/image/exit1.png"));
        exitPush->setFlat(1);//设置按钮的透明属性

        //connect(againPush,SIGNAL(clicked(bool)),this,SLOT(M_againPush()));
        connect(exitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));

}

void doublegame::timeOut()
{

    if(snake1.length()==20 || snake2.length()==20)
    {
         timer->start(time/2);
    }


     switch (moveFlage1) {
         case 1:
             addTopRectF1();
             break;
         case 2:
             addDownRectF1();
             break;
         case 4:
             addRightRectF1();
             break;
         case 3:
             addLeftRectF1();
             break;
         default:
             break;
         }

     switch (moveFlage2) {
         case 1:
             addTopRectF2();
             break;
         case 2:
             addDownRectF2();
             break;
         case 4:
             addRightRectF2();
             break;
         case 3:
             addLeftRectF2();
             break;
         default:
             break;
         }
      deleteLastRectF();

    update();
    for(int i=0; i<rewardNode.length(); i++)
    {
        if(rewardNode.at(i).contains(snake1.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2))){

            rewardNode.removeAt(i);
            switch (moveFlage1) {
            case 1:
                addTopRectF1();
                break;
            case 2:
                addDownRectF1();
                break;
            case 4:
                addRightRectF1();
                break;
            case 3:
                addLeftRectF1();
                break;
            default:
                break;
            }
            break;
        }

        if(rewardNode.at(i).contains(snake2.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2))){

            rewardNode.removeAt(i);
            switch (moveFlage2) {
            case 1:
                addTopRectF2();
                break;
            case 2:
                addDownRectF2();
                break;
            case 4:
                addRightRectF2();
                break;
            case 3:
                addLeftRectF2();
                break;
            default:
                break;
            }
            break;
        }
    }

    for(int i=0;i<barrier.length();i++)
    {
        if(barrier.at(i).contains(snake1.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2)))
        {
            gameIsOver=true;
            winner=2;
        }

        if(barrier.at(i).contains(snake2.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2)))
        {
            gameIsOver=true;
            winner=1;
        }
    }

}
void doublegame::barrierTimeOut()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if(barrier.length()>100)
    {
        for(int i=0;i<10;i++)
        {
            barrier.removeFirst();
        }
    }
    barrier.append(QRectF(qrand()%(this->width()/20)*20,qrand()%(this->height()/20)*20,snakeNodeWidth,snakeNodeWidth));
    for(int i=0;i<10;i++)
    {
        int dir=qrand()%2;
        switch (dir) {
        case 0:
            //向右
            barrier.append(QRectF(barrier.at(barrier.length()-1).x()+snakeNodeWidth,barrier.at(barrier.length()-1).y(),snakeNodeWidth,snakeNodeHeight));
            break;
        case 1:
            //向下
             barrier.append(QRectF(barrier.at(barrier.length()-1).x(),barrier.at(barrier.length()-1).y()-snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
            break;
        }
    }

}
void doublegame::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up:
        if(moveFlage1 != 2){
            moveFlage1 = 1;
        }
        break;
    case Qt::Key_Down:
        if(moveFlage1 != 1){
            moveFlage1 = 2;
        }
        break;
    case Qt::Key_Right:
        if(moveFlage1 != 3){
            moveFlage1 = 4;
        }
        break;
    case Qt::Key_Left:
        if(moveFlage1 != 4){
            moveFlage1 = 3;
        }
        break;
    case Qt::Key_W:
        if(moveFlage2 != 2){
            moveFlage2 = 1;
        }
        break;
    case Qt::Key_S:
        if(moveFlage2 != 1){
            moveFlage2 = 2;
        }
        break;
    case Qt::Key_D:
        if(moveFlage2 != 3){
            moveFlage2 = 4;
        }
        break;
    case Qt::Key_A:
        if(moveFlage2 != 4){
            moveFlage2 = 3;
        }
        break;


    case Qt::Key_End:
        finish=true;
        break;
    default:
        break;
    }
}
void doublegame::rewardTimeOut()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if(rewardNode.length() > 10){
        rewardNode.removeAt(qrand()%5);
    }
    int x=qrand()%(this->width()/20)*20;
    int y=qrand()%(this->height()/20)*20;
    if(x==0 || x==20) x+=20;
    if(x==1380 || x==1360)  x-=20;
    if(y==0 || y==20) y+=20;
    if(y==640 || y==620)  y-=20;
    rewardNode.append(QRectF(x,y,snakeNodeWidth,snakeNodeWidth));


}
void doublegame::addTopRectF1()
{
    if(snake1.at(0).y()-snakeNodeHeight < 0){
        snake1.insert(0,QRectF(QPointF(snake1.at(0).x(),this->height()-snakeNodeHeight),
                              QPointF(snake1.at(0).x()+snakeNodeWidth,this->height())));
    }else{
         snake1.insert(0,QRectF(snake1.at(0).x(),snake1.at(0).y()-snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
    }
}
//向下移动
void doublegame::addDownRectF1()
{
    if(snake1.at(0).y()+snakeNodeHeight*2 > this->height()){
        snake1.insert(0,QRectF(QPointF(snake1.at(0).x(),snakeNodeHeight),
                              QPointF(snake1.at(0).x()+snakeNodeWidth,0)));
    }else{
        snake1.insert(0,QRectF(snake1.at(0).x(),snake1.at(0).y()+snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
    }
}
//向左移动
void doublegame::addLeftRectF1()
{
    if(snake1.at(0).x()-snakeNodeWidth < 0){
        snake1.insert(0,QRectF(QPointF(this->width()-snakeNodeWidth,snake1.at(0).y()),
                              QPointF(this->width(),snake1.at(0).y()+snakeNodeHeight)));
    }else{
        snake1.insert(0,QRectF(snake1.at(0).x()-snakeNodeWidth,snake1.at(0).y(),snakeNodeWidth,snakeNodeHeight));
    }
}
//向右移动
void doublegame::addRightRectF1()
{
    if(snake1.at(0).x()+snakeNodeWidth*2 > this->width()){
        snake1.insert(0,QRectF(QPointF(0,snake1.at(0).y()),
                              QPointF(snakeNodeWidth,snake1.at(0).y()+snakeNodeHeight)));
    }else{
        snake1.insert(0,QRectF(snake1.at(0).x()+snakeNodeWidth,snake1.at(0).y(),snakeNodeWidth,snakeNodeHeight));
    }
}

void doublegame::addTopRectF2()
{
    if(snake2.at(0).y()-snakeNodeHeight < 0){
        snake2.insert(0,QRectF(QPointF(snake2.at(0).x(),this->height()-snakeNodeHeight),
                              QPointF(snake2.at(0).x()+snakeNodeWidth,this->height())));
    }else{
         snake2.insert(0,QRectF(snake2.at(0).x(),snake2.at(0).y()-snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
    }
}
//向下移动
void doublegame::addDownRectF2()
{
    if(snake2.at(0).y()+snakeNodeHeight*2 > this->height()){
        snake2.insert(0,QRectF(QPointF(snake2.at(0).x(),snakeNodeHeight),
                              QPointF(snake2.at(0).x()+snakeNodeWidth,0)));
    }else{
        snake2.insert(0,QRectF(snake2.at(0).x(),snake2.at(0).y()+snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
    }
}
//向左移动
void doublegame::addLeftRectF2()
{
    if(snake2.at(0).x()-snakeNodeWidth < 0){
        snake2.insert(0,QRectF(QPointF(this->width()-snakeNodeWidth,snake2.at(0).y()),
                              QPointF(this->width(),snake2.at(0).y()+snakeNodeHeight)));
    }else{
        snake2.insert(0,QRectF(snake2.at(0).x()-snakeNodeWidth,snake2.at(0).y(),snakeNodeWidth,snakeNodeHeight));
    }
}
//向右移动
void doublegame::addRightRectF2()
{
    if(snake2.at(0).x()+snakeNodeWidth*2 > this->width()){
        snake2.insert(0,QRectF(QPointF(0,snake2.at(0).y()),
                              QPointF(snakeNodeWidth,snake2.at(0).y()+snakeNodeHeight)));
    }else{
        snake2.insert(0,QRectF(snake2.at(0).x()+snakeNodeWidth,snake2.at(0).y(),snakeNodeWidth,snakeNodeHeight));
    }
}
void doublegame::deleteLastRectF()
{
    snake1.removeLast();
    snake2.removeLast();

}

void doublegame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    QFont font("方正舒体",12,QFont::ExtraLight,false);

    //反锯齿
    painter.setRenderHint(QPainter::Antialiasing);

   // pen.setColor(Qt::transparent);

    pen.setColor(Qt::white);
    brush.setColor(QColor(236,170,218,100));
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);


    //画蛇
    painter.drawEllipse(snake1.at(0).x(),snake1.at(0).y(),20,20);
    for(int i=1; i<snake1.length(); i++){
        painter.drawRect(snake1.at(i));
    }
    brush.setColor(QColor(100,100,100,255));
    painter.setBrush(brush);

    painter.drawEllipse(snake2.at(0).x(),snake2.at(0).y(),20,20);
    for(int i=1; i<snake2.length(); i++){
        painter.drawRect(snake2.at(i));
    }
    brush.setColor(QColor(100,100,100,255));
    painter.setBrush(brush);



    //画墙
    brush.setColor(QColor(0,0,0,200));
    painter.setBrush(brush);

    painter.drawRect(0,0,this->width(),20);
    painter.drawRect(0,0,20,this->height());
    painter.drawRect(0,this->height()-20,this->width(),20);
    painter.drawRect(this->width()-20,0,20,this->height());

    //画食物

    brush.setColor(QColor(243,137,66,200));
    painter.setBrush(brush);

    for(int i=0; i<rewardNode.length(); i++){
        painter.drawEllipse(rewardNode.at(i));
    }

    brush.setColor(QColor(0,0,0,200));
    painter.setBrush(brush);

    //画障碍物
    for(int i=0;i<barrier.length();i++)
    {
        painter.drawRect(barrier.at(i));
    }



     pen.setColor(Qt::white);

     if(snakeStrike()  || snakeOut() || gameIsOver){

        brush.setColor(QColor(0,0,0,100));
        painter.drawRect(0,0,1400,660);
        QFont font("汉仪铸字木头人W",50,QFont::ExtraLight,false);
        painter.setFont(font);
        painter.drawText((this->width()-500)/2,(this->height()-30)/2,QString("GAME OVER!"));

        if(winner==1)
        {
             painter.drawText((this->width()-660)/2,(this->height()-300)/2,QString("WINNER : PURPLE "));
        }
        if(winner==2)
        {
             painter.drawText((this->width()-660)/2,(this->height()-300)/2,QString("WINNER : BLACK "));
        }


      /*  againPush->setIconSize(QSize(100,100));
        againPush->setGeometry(650,360,100,100);
*/
        exitPush->setIconSize(QSize(250,250));
        exitPush->setGeometry(600,380,160,80);

        timer->stop();
        rewardTimer->stop();
        gameOver = true;


    }

    if(finish)
    {

        brush.setColor(QColor(0,0,0,100));
        painter.drawRect(0,0,1400,660);
        QFont font("汉仪铸字木头人W",100,QFont::ExtraLight,false);
        painter.setFont(font);
        painter.drawText((this->width()-300)/2,(this->height()-30)/2,QString("END"));


       /* againPush->setIconSize(QSize(100,100));
        againPush->setGeometry(650,360,100,100);*/

        exitPush->setIconSize(QSize(250,250));
        exitPush->setGeometry(600,380,160,80);

        timer->stop();
        rewardTimer->stop();
        gameOver = true;
    }

    QWidget::paintEvent(event);

}
bool doublegame::snakeStrike()
{
    for(int i=0; i<snake1.length(); i++){
        for(int j=i+1; j<snake1.length(); j++){
            if(snake1.at(i) == snake1.at(j)){
                winner=2;
                return true;
            }
        }
    }

    for(int i=0; i<snake2.length(); i++){
        for(int j=i+1; j<snake2.length(); j++){
            if(snake2.at(i) == snake2.at(j)){
                winner=1;
                return true;
            }
        }
    }

    for(int i=1;i<snake1.length();i++)
    {
        if(snake1.at(i)==snake2.at(0))
        {
            winner=1;
            return true;
        }

    }


    for(int i=1;i<snake2.length();i++)
    {
        if(snake2.at(i)==snake1.at(0))
        {
            winner=2;
            return true;
        }

    }

    return false;


}

bool doublegame::snakeOut()
{
    if(snake1.at(0).x()<20 || snake1.at(0).y()<20 || snake1.at(0).x()>1379 || snake1.at(0).y()>639)
    {
        winner=2;
        return true;
    }

    if(snake2.at(0).x()<20 || snake2.at(0).y()<20 || snake2.at(0).x()>1379 || snake2.at(0).y()>639)
    {
        winner=1;
        return true;
    }



    return  false;
}
/*
void doublegame::M_againPush()
{
    doublegamewindow=new doublegame(this);
    doublegamewindow->show();
}

*/
void doublegame::M_exitPush()
{
    this->close();

    //gamewindow=new game(this);  //创建一个新的界面，任然以原来的界面为父窗口，退出后可以直接回到上一个界面。
    //gamewindow->show();

}
