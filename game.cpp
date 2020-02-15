
#include "game.h"
#include "model.h"



extern int place;
extern int player;

game::game(QWidget *parent) : QWidget(parent)
{

    //使键盘响应
    this->grabKeyboard();


    //界面控制
    this->setAutoFillBackground(true);//设置父窗口背景可被覆盖填充
    this->resize(1400,660);
    this->setWindowTitle("阿钪的全世界的最可爱的贪吃蛇");



    this->setWindowIcon(QIcon(":/new/prefix1/image/庙门.PNG"));

    //选背景
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

        snake.append(QRectF(snakeNodeWidth*30,snakeNodeHeight*19,snakeNodeWidth,snakeNodeHeight));
        addTopRectF();
        addTopRectF();


      //首先生成一个食物
      rewardNode.append(QRectF(qrand()%(this->width()/20)*20,qrand()%(this->height()/20)*20,snakeNodeWidth,snakeNodeWidth));



      //设置传送门
      left.setX(18*20);
      left.setY(16*20);

      right.setX(50*20);
      right.setY(16*20);

      center.setX(34*20);
      center.setY(16*20);


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
      barrierTimer->start(time*200);






      //设置按钮

      exitPush=new QPushButton(this);
      exitPush->setIconSize(QSize(0,0));
      exitPush->setGeometry(0,0,0,0);
      exitPush->setIcon(QIcon(":/new/prefix1/image/exit1.png"));
      exitPush->setFlat(1);//设置按钮的背景透明属性

      connect(exitPush,SIGNAL(clicked(bool)),this,SLOT(M_exitPush()));
}

//走一步并检查
void game::timeOut()
{

    //检查是否进入传从门
    if(snake.at(0).x()==center.x() && snake.at(0).y() == center.y()  )
    {

        int i=qrand()%2;

        if(i==0)
        {
            snake.insert(0,QRectF(right.x(),right.y(),snakeNodeWidth,snakeNodeHeight));

        }

        if(i==1)
        {
            snake.insert(0,QRectF(left.x(),left.y(),snakeNodeWidth,snakeNodeHeight));
        }



         deleteLastRectF();

    }



    //检查身长是否超过10  超10加速
    if(snake.length()==10)
    {
         timer->start(time/2);
    }


    //移动
     switch (moveFlage) {
         case 1:
             addTopRectF();
             break;
         case 2:
             addDownRectF();
             break;
         case 4:
             addRightRectF();
             break;
         case 3:
             addLeftRectF();
             break;
         default:
             break;
         }
      deleteLastRectF();




    //检查是否吃到普通食物
    for(int i=0; i<rewardNode.length(); i++)
    {
        if(rewardNode.at(i).contains(snake.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2)))
        {

            rewardNode.removeAt(i);
            switch (moveFlage) {
            case 1:
                addTopRectF();
                break;
            case 2:
                addDownRectF();
                break;
            case 4:
                addRightRectF();
                break;
            case 3:
                addLeftRectF();
                break;
            default:
                break;
            }
            break;
        }
    }

    //检查是否吃到减一节食物
    for(int i=0; i<lessNode.length(); i++)
    {
        if(lessNode.at(i).contains(snake.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2)))
        {

            lessNode.removeAt(i);
            snake.removeLast();
        }
    }

    //检查是否吃到长两节食物
    for(int i=0; i<doubleRewardNode.length(); i++)
    {
        if(doubleRewardNode.at(i).contains(snake.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2)))
        {

            doubleRewardNode.removeAt(i);
            switch (moveFlage) {
            case 1:
                addTopRectF();
                addTopRectF();
                break;
            case 2:
                addDownRectF();
                addDownRectF();
                break;
            case 4:
                addRightRectF();
                addRightRectF();
                break;
            case 3:
                addLeftRectF();
                addLeftRectF();
                break;
            default:
                break;
            }

        }
    }

    //检测是否撞到障碍物
    for(int i=0;i<barrier.length();i++)
    {
        if(barrier.at(i).contains(snake.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2)))
        {
            gameIsOver=true;
        }
    }
    update();


}

//发吃的
void game::rewardTimeOut()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if(rewardNode.length() > 3){
        rewardNode.removeAt(qrand()%3);
    }


    int xx=qrand()%(this->width()/snakeNodeWidth)*snakeNodeWidth;

    int yy=qrand()%(this->height()/snakeNodeHeight)*snakeNodeHeight;

    if(xx==0 || xx==20) xx+=20;
    if(xx==1380 || xx==1360)  xx-=20;
    if(yy==0 || yy==20) yy+=20;
    if(yy==640 || yy==620)  yy-=20;
    rewardNode.append(QRectF(xx,yy,snakeNodeWidth,snakeNodeWidth));
    bool flag=false;

    //检查是否与蛇身重复
    for(int i=0;i<snake.length();i++)
    {
        if(xx==snake.at(i).x() && yy==snake.at(i).y())
        {
            flag=true;
            break;
        }
    }
    //检查是否与普通食物重复
    for(int i=0;i<rewardNode.length();i++)
    {
        if(xx==rewardNode.at(i).x() && yy==rewardNode.at(i).y())
        {
            flag=true;
            break;
        }
    }
    //检查是否与减一节食物重复
    for(int i=0;i<lessNode.length();i++)
    {
        if(xx==lessNode.at(i).x() && yy==lessNode.at(i).y())
        {
            flag=true;
            break;
        }
    }
    //检查是否与加两节食物重复
    for(int i=0;i<doubleRewardNode.length();i++)
    {
        if(xx==doubleRewardNode.at(i).x() && yy==doubleRewardNode.at(i).y())
        {
            flag=true;
            break;
        }
    }


    if(!flag)
    {
        int kindOfFood=qrand()%20;
        switch(kindOfFood)
        {
         case 13:
            lessNode.append(QRectF(xx,yy,snakeNodeWidth,snakeNodeWidth));
            break;

         case 17:
            doubleRewardNode.append(QRectF(xx,yy,snakeNodeWidth,snakeNodeWidth));
            break;

        default:
            rewardNode.append(QRectF(xx,yy,snakeNodeWidth,snakeNodeWidth));


        }
    }








}

//产生障碍物
void game::barrierTimeOut()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if(barrier.length()>200)
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
void game::addTopRectF()
{
    /*if(snake.at(0).y()-snakeNodeHeight < 0){
        snake.insert(0,QRectF(QPointF(snake.at(0).x(),this->height()-snakeNodeHeight),
                              QPointF(snake.at(0).x()+snakeNodeWidth,this->height())));
    }else{
         snake.insert(0,QRectF(snake.at(0).x(),snake.at(0).y()-snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
    }*/

    snake.insert(0,QRectF(snake.at(0).x(),snake.at(0).y()-snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
}
//向下移动
void game::addDownRectF()
{
    /*if(snake.at(0).y()+snakeNodeHeight*2 > this->height()){
        snake.insert(0,QRectF(QPointF(snake.at(0).x(),snakeNodeHeight),
                              QPointF(snake.at(0).x()+snakeNodeWidth,0)));
    }else{
        snake.insert(0,QRectF(snake.at(0).x(),snake.at(0).y()+snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
    }*/
    snake.insert(0,QRectF(snake.at(0).x(),snake.at(0).y()+snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
}
//向左移动
void game::addLeftRectF()
{
    /*if(snake.at(0).x()-snakeNodeWidth < 0){
        snake.insert(0,QRectF(QPointF(this->width()-snakeNodeWidth,snake.at(0).y()),
                              QPointF(this->width(),snake.at(0).y()+snakeNodeHeight)));
    }else{
        snake.insert(0,QRectF(snake.at(0).x()-snakeNodeWidth,snake.at(0).y(),snakeNodeWidth,snakeNodeHeight));
    }*/

    snake.insert(0,QRectF(snake.at(0).x()-snakeNodeWidth,snake.at(0).y(),snakeNodeWidth,snakeNodeHeight));
}
//向右移动
void game::addRightRectF()
{
    /*if(snake.at(0).x()+snakeNodeWidth*2 > this->width()){
        snake.insert(0,QRectF(QPointF(0,snake.at(0).y()),
                              QPointF(snakeNodeWidth,snake.at(0).y()+snakeNodeHeight)));
    }else{
        snake.insert(0,QRectF(snake.at(0).x()+snakeNodeWidth,snake.at(0).y(),snakeNodeWidth,snakeNodeHeight));
    }*/

     snake.insert(0,QRectF(snake.at(0).x()+snakeNodeWidth,snake.at(0).y(),snakeNodeWidth,snakeNodeHeight));
}
//删除结尾数据
void game::deleteLastRectF()
{
    snake.removeLast();

}

void game::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;


    //反锯齿
    painter.setRenderHint(QPainter::Antialiasing);



    //pen用来画边框
    pen.setColor(Qt::white);
    painter.setPen(pen);

    brush.setColor(QColor(236,170,218,100));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);


    //画蛇
    painter.drawEllipse(snake.at(0).x(),snake.at(0).y(),20,20);
    for(int i=1; i<snake.length(); i++){
        painter.drawRect(snake.at(i));
    }

    //画普通食物
    brush.setColor(QColor(243,137,66,200));
    painter.setBrush(brush);

    for(int i=0; i<rewardNode.length(); i++){
        painter.drawEllipse(rewardNode.at(i));
    }

    //画传送门
    brush.setColor(QColor(200,200,200,100));
    painter.setBrush(brush);

    painter.drawRect(left.x(),left.y(),snakeNodeWidth,snakeNodeHeight);
     painter.drawRect(right.x(),right.y(),snakeNodeWidth,snakeNodeHeight);

     brush.setColor(QColor(0,255,255,100));
     painter.setBrush(brush);
     painter.drawRect(center.x(),center.y(),snakeNodeWidth,snakeNodeHeight);


     //画墙
     brush.setColor(QColor(0,0,0,200));
     painter.setBrush(brush);

     painter.drawRect(0,0,this->width(),20);
     painter.drawRect(0,0,20,this->height());
     painter.drawRect(0,this->height()-20,this->width(),20);
     painter.drawRect(this->width()-20,0,20,this->height());


    //画加两节食物（牛油果）
    brush.setColor(QColor(71,147,89,255));
    painter.setBrush(brush);

    for(int i=0; i<doubleRewardNode.length(); i++){
        painter.drawEllipse(doubleRewardNode.at(i));
    }

    //画减一节食物（白色）
    brush.setColor(QColor(255,255,255,255));
    painter.setBrush(brush);

    for(int i=0; i<lessNode.length(); i++){
        painter.drawEllipse(lessNode.at(i));
    }


    //画障碍物
    brush.setColor(QColor(0,0,0,200));
    painter.setBrush(brush);

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
        QFont font1("汉仪铸字木头人W",30,QFont::Light,false);
        painter.setFont(font1);
        painter.drawText((this->width()-500)/2+130,(this->height()-30)/2+60,QString("SCORE:"));
        painter.drawText((this->width()-500)/2+300,(this->height()-30)/2+60,QString::number(snake.length()));


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



        exitPush->setIconSize(QSize(250,250));
        exitPush->setGeometry(600,380,160,80);

        timer->stop();
        rewardTimer->stop();
        gameOver = true;
    }

    QWidget::paintEvent(event);

}


void game::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up:
        if(moveFlage != 2){
            moveFlage = 1;
        }
        break;
    case Qt::Key_Down:
        if(moveFlage != 1){
            moveFlage = 2;
        }
        break;
    case Qt::Key_Right:
        if(moveFlage != 3){
            moveFlage = 4;
        }
        break;
    case Qt::Key_Left:
        if(moveFlage != 4){
            moveFlage = 3;
        }
        break;
    case Qt::Key_End:
        finish=true;
        break;
    default:
        break;
    }
}

bool game::snakeStrike()
{
    for(int i=0; i<snake.length(); i++){
        for(int j=i+1; j<snake.length(); j++){
            if(snake.at(i) == snake.at(j)){
                return true;
            }
        }
    }
    return false;


}

bool game::snakeOut()
{
    if(snake.at(0).x()<20 || snake.at(0).y()<20 || snake.at(0).x()>1379 || snake.at(0).y()>639)
        return true;
    return  false;
}


void game::M_exitPush()
{


       this->close();
  //  widgtwindow=new widget(this);  //创建一个新的界面，任然以原来的界面为父窗口，退出后可以直接回到上一个界面。
    //widgetwindow->show();

}
