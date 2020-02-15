#include "ai.h"
#include "widget.h"
#include<QQueue>


AI::AI(QWidget *parent) : QWidget(parent)
{



   //界面控制
    this->setAutoFillBackground(true);//设置父窗口背景可被覆盖填充
    this->resize(660,660);


    this->setWindowIcon(QIcon(":/new/prefix1/image/MiaoMenXiao.PNG"));

    QPalette palette;

    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/image/MiaoMenXiao.PNG").scaled(this->size())));


    this->setPalette(palette);
    this->setWindowTitle("AI");


    //有关按钮
   goBack=new QPushButton(this);
   goBack->setIconSize(QSize(100,100));
   goBack->setGeometry(750,500,100,100);
   goBack->setIcon(QIcon(":/new/prefix1/image/exit1.png"));
   goBack->setFlat(1);

    // connect(goBack,&QPushButton::clicked,this,&AI::sendGOBackSignals);

    //connect(goBack,&QPushButton::clicked,this,&AI::sendGOBackSignals);

    connect(goBack,SIGNAL(clicked(bool)),this,SLOT(sendGOBackSignals()));

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    //生成初始的蛇
       //   snake.append(QRectF(QRectF(qrand()%(this->width()/20)*20,qrand()%(this->height()/20)*20,snakeNodeWidth,snakeNodeHeight)));
       snake.append(cube(snakeNodeWidth*10,snakeNodeHeight*20));
       addTopRectF();
       addTopRectF();


     //首先生成一个奖励节点
     //rewardNode.append(QRectF(snakeNodeWidth*11,snakeNodeHeight*5,snakeNodeWidth,snakeNodeHeight));
   //  rewardNode.append(QRectF(qrand()%(this->width()/20)*20,qrand()%(this->height()/20)*20,snakeNodeWidth,snakeNodeWidth));

     food.x=(qrand()%(this->height()/20))*20;
    food.y=(qrand()%(this->height()/20))*20;

    // food
     //设置刷新时间
    timer = new QTimer;
     connect(timer, SIGNAL(timeout()),this,SLOT(timeOut()));
     timer->start(time);

}


void AI::sendGOBackSignals()
{
    emit backSignals();
    //this->show();
}


void AI::addTopRectF()
{
    /*if(snake.at(0).y()-snakeNodeHeight < 0){
        snake.insert(0,QRectF(QPointF(snake.at(0).x(),this->height()-snakeNodeHeight),
                              QPointF(snake.at(0).x()+snakeNodeWidth,this->height())));
    }else{
         snake.insert(0,QRectF(snake.at(0).x(),snake.at(0).y()-snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
    }*/

    snake.insert(0,cube(snake.at(0).x,snake.at(0).y-snakeNodeHeight));
}
//向下移动
void AI::addDownRectF()
{
    /*if(snake.at(0).y()+snakeNodeHeight*2 > this->height()){
        snake.insert(0,QRectF(QPointF(snake.at(0).x(),snakeNodeHeight),
                              QPointF(snake.at(0).x()+snakeNodeWidth,0)));
    }else{
        snake.insert(0,QRectF(snake.at(0).x(),snake.at(0).y()+snakeNodeHeight,snakeNodeWidth,snakeNodeHeight));
    }*/
    snake.insert(0,cube(snake.at(0).x,snake.at(0).y+snakeNodeHeight));
}
//向左移动
void AI::addLeftRectF()
{
    /*if(snake.at(0).x()-snakeNodeWidth < 0){
        snake.insert(0,QRectF(QPointF(this->width()-snakeNodeWidth,snake.at(0).y()),
                              QPointF(this->width(),snake.at(0).y()+snakeNodeHeight)));
    }else{
        snake.insert(0,QRectF(snake.at(0).x()-snakeNodeWidth,snake.at(0).y(),snakeNodeWidth,snakeNodeHeight));
    }*/

    snake.insert(0,cube(snake.at(0).x-snakeNodeWidth,snake.at(0).y));
}
//向右移动
void AI::addRightRectF()
{
    /*if(snake.at(0).x()+snakeNodeWidth*2 > this->width()){
        snake.insert(0,QRectF(QPointF(0,snake.at(0).y()),
                              QPointF(snakeNodeWidth,snake.at(0).y()+snakeNodeHeight)));
    }else{
        snake.insert(0,QRectF(snake.at(0).x()+snakeNodeWidth,snake.at(0).y(),snakeNodeWidth,snakeNodeHeight));
    }*/

     snake.insert(0,cube(snake.at(0).x+snakeNodeWidth,snake.at(0).y));
}


void AI::paintEvent(QPaintEvent *event)
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
    painter.drawEllipse(snake.at(0).x,snake.at(0).y,20,20);
    for(int i=1; i<snake.length(); i++){
        painter.drawRect(snake.at(i).x,snake.at(i).y,snakeNodeWidth,snakeNodeHeight)  ;
    }

    //画普通食物
    brush.setColor(QColor(243,137,66,200));
    painter.setBrush(brush);


    painter.drawEllipse(food.x,food.y,snakeNodeWidth,snakeNodeHeight);





     pen.setColor(Qt::white);

  if(snakeStrike()  || snakeOut() || gameIsOver){

        brush.setColor(QColor(0,0,0,200));
        painter.setBrush(brush);
        painter.drawRect(0,0,660,660);
        QFont font("汉仪铸字木头人W",50,QFont::ExtraLight,false);
        painter.setFont(font);
        painter.drawText((this->width()-500)/2,(this->height()-30)/2,QString("GAME OVER!"));

        goBack->setIconSize(QSize(0,0));
         goBack->setGeometry(260,360,160,80);
        timer->stop();

        gameOver = true;


    }

    if(finish)
    {

        brush.setColor(QColor(0,0,0,100));
        painter.drawRect(0,0,1400,660);
        QFont font("汉仪铸字木头人W",100,QFont::ExtraLight,false);
        painter.setFont(font);
        painter.drawText((this->width()-300)/2,(this->height()-30)/2,QString("END"));




        timer->stop();

        gameOver = true;
    }

    QWidget::paintEvent(event);

}

bool AI::snakeStrike()
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

bool AI::snakeOut()
{
    if(snake.at(0).x<0 || snake.at(0).y<0 || snake.at(0).x>661 || snake.at(0).y>661)
        return true;
    return  false;
}

void AI::deleteLastRectF()
{
    snake.removeLast();

}
/*
void AI::timeOut()
{

    if(food.x==snake.at(0).x && food.y==snake.at(0).y)
    {

        food.x=qrand()%(this->width()/20)*20;
        food.y=qrand()%(this->width()/20)*20;
        if(food.x==0) food.x+=20;
        if(food.x==640) food.x-=20;
        if(food.y==0)food.y+=20;
         if(food.y==640)food.y-=20;
        while(snake.count(food))
        {
            food.x=qrand()%(this->width()/20)*20;
            food.y=qrand()%(this->width()/20)*20;
            if(food.x==0) food.x+=20;
            if(food.x==640) food.x-=20;
            if(food.y==0)food.y+=20;
            if(food.y==640)food.y-=40;
        }


        switch (moveFlage) {
        case 1:
            addTopRectF();
            break;
        case 3:
            addDownRectF();
            break;
        case 0:
            addRightRectF();
            break;
        case 2:
            addLeftRectF();
            break;
        default:
            break;
        }
    }

    QQueue<cube> bfs;
    QList<cube> visited;
    cube tmp;
    const int next[4][2] = { { snakeNodeWidth,0 } ,{ 0,snakeNodeWidth },{ -snakeNodeWidth,0 },{ 0,-snakeNodeWidth } };

    int flag=0;
    cube start;
    for(int i=0;i<4;i++)
    {
        for(int k=0;k<bfs.length();k++)
        {
             bfs.removeAt(k);
        }

        start.x=snake.at(0).x+next[i][0];
        start.y=snake.at(0).x+next[i][1];
        bfs.append(start);

        for(int i=0;i<snake.length()-1;i++)
        {
            visited.append(snake.at(i));
        }

        while(!bfs.isEmpty())
        {
            for(int k=0;k<4;k++)
            {
                tmp.x=bfs.at(0).x + next[k][0];
                tmp.y=bfs.at(0).y + next[k][1];
                //出界
                if(snake.at(0).x<0 || snake.at(0).y<0 || snake.at(0).x>640 || snake.at(0).y>640)
                    continue;

                //入队
                if(!visited.count(tmp))
                {
                    tmp.step=bfs.front().step+1;
                    visited.append(tmp);
                    bfs.append(tmp);
                }

                if(tmp==food)
                {
                    moveFlage=i;
                    flag=1;
                    break;
                }

            }

            if(flag) break;

            bfs.pop_front();
        }

        switch (moveFlage) {
        case 1:
            addTopRectF();
            break;
        case 3:
            addDownRectF();
            break;
        case 0:
            addRightRectF();
            break;
        case 2:
            addLeftRectF();
            break;
        default:
            break;
        }
        deleteLastRectF();




     update();
   }

}



*/




void AI::timeOut()
{


    if(food.x==snake.at(0).x && food.y==snake.at(0).y)
    {

        food.x=qrand()%(this->width()/20)*20;
        food.y=qrand()%(this->width()/20)*20;
        if(food.x==0) food.x+=20;
        if(food.x==640) food.x-=20;
        if(food.y==0)food.y+=20;
         if(food.y==640)food.y-=20;
        while(snake.count(food))
        {
            food.x=qrand()%(this->width()/20)*20;
            food.y=qrand()%(this->width()/20)*20;
            if(food.x==0) food.x+=20;
            if(food.x==640) food.x-=20;
            if(food.y==0)food.y+=20;
            if(food.y==640)food.y-=40;
        }


        switch (moveFlage) {
        case 1:
            addTopRectF();
            break;
        case 3:
            addDownRectF();
            break;
        case 0:
            addRightRectF();
            break;
        case 2:
            addLeftRectF();
            break;
        default:
            break;
        }


    }
    const int next[4][2] = { { snakeNodeWidth,0 } ,{ 0,-snakeNodeWidth },{ -snakeNodeWidth,0 },{ 0,snakeNodeWidth } };

    int ans[4];
    for(int i=0;i<4;i++)
    {
        ans[i]=i;
    }
    for(int i=0;i<4;i++)
    {
        cube tmp;
        tmp.x=snake.at(0).x+next[i][0];
        tmp.y=snake.at(0).y+next[i][1];

        if(snake.count(tmp) || tmp.x<0 || tmp.y<0 || tmp.x>640 ||tmp.y>640)
        {
            ans[i]=-1;
        }
    }


     if(snake.at(0).x>food.x)
     {


         if(moveFlage!= 0 && ans[2]!=-1)
         {
             moveFlage=2;
         }

         else if(ans[2]==-1)
         {


             for(int i=0;i<4;i++)
               {
                   if(ans[i]!=-1) moveFlage=ans[i];
               }


         }

     }

     if(snake.at(0).x<food.x)
     {


         if(moveFlage!= 2 && ans[0]!=-1)
         {
             moveFlage=0;
         }

         else if(ans[0]==-1)
         {

          for(int i=0;i<4;i++)
             {
                 if(ans[i]!=-1) moveFlage=ans[i];
             }

         }

     }

     if(snake.at(0).x==food.x && snake.at(0).y<food.y)
     {



         if(moveFlage!= 1 && ans[3]!=-1)
         {
             moveFlage=3;
         }

         else if(ans[3]==-1)
         {

             for(int i=0;i<4;i++)
             {
                 if(ans[i]!=-1) moveFlage=ans[i];
             }

         }

     }

     if(snake.at(0).x==food.x && snake.at(0).y>food.y)
     {



         if(moveFlage!= 3 && ans[1]!=-1)
         {
             moveFlage=1;
         }

         else if(ans[1]==-1)
         {



            for(int i=0;i<4;i++)
             {
                 if(ans[i]!=-1) moveFlage=ans[i];
             }

         }

     }




    switch (moveFlage) {
    case 1:
        addTopRectF();
        break;
    case 3:
        addDownRectF();
        break;
    case 0:
        addRightRectF();
        break;
    case 2:
        addLeftRectF();
        break;
    default:
        break;
    }
    deleteLastRectF();




 update();
}



/*int AI::getNextCmd()
{
    QQueue<cube> bfs;
    QList<cube> visited;
    cube tmp;
    const int next[4][2] = { { snakeNodeWidth,0 } ,{ 0,snakeNodeWidth },{ -snakeNodeWidth,0 },{ 0,-snakeNodeWidth } };

   // bfs.append(snake.at(0));




    for(int i=0;i<snake.length()-1;i++)
    {
        visited.append(snake.at(i));
    }

    //如果终点是尾巴就把尾巴设为可走
    if(food != snake.back())
    {
        visited.append(snake.back());
    }

    int count[4];

    while(!bfs.isEmpty())
    {
        for(int k=0;k<4;k++)
        {
            tmp.x=bfs.at(0).x + next[k][0];
            tmp.y=bfs.at(0).y + next[k][1];
            //出界
            if(tmp.x<0 || tmp.y<0 ||tmp.x>640 || tmp.y>640)
                continue;

            //入队
            if(!visited.count(tmp))
            {
                tmp.step=bfs.front().step+1;
                visited.append(tmp);
                bfs.append(tmp);
            }

            if(tmp==food)
            {
                return tmp.step;
            }



        }

        bfs.pop_front();
    }


}
int  AI::getNextCmd()
{
    int cmd=moveFlage;
    //如果能找到食物
    if(canFindFood(snake.at(0)))
    {
        //模拟一条蛇 记录原蛇参数
         QList<cube> fakesnake;
         for(int i=0;i<snake.length();i++)
         {
             fakesnake.append(snake.at(i));
         }

         //让蛇去吃食物
         int foodExit=1;
         while(foodExit)
         {
             int order=nextCmdToFood();
             if(order==-1)  order=0;
             switch (order) {
                 case 1:
                     addTopRectF();
                     break;
                 case 3:
                     addDownRectF();
                     break;
                 case 0:
                     addRightRectF();
                     break;
                 case 2:
                     addLeftRectF();
                     break;
                 default:
                     break;
                 }
              deleteLastRectF();

            if(snake.front().x==food.x  &&  snake.front().y==food.y)
            {
                foodExit=0;
            }
         }
         for(int i=0;i<snake.length();i++)
         {
             snake.removeAt(i);
           //snake.append(fakesnake.at(i));

         }
         for(int i=0;i<snake.length();i++)
         {

           snake.append(fakesnake.at(i));

         }
         //如果吃完还能找到尾巴/到尾巴的距离大于1  ---> 真的去吃
         if(canFindPath(snake.at(0),snake.back())>1)
         {
                 cmd=nextCmdToFood();

         }
         else {
             cmd=nextCmdTOFarAway(snake.at(0));
         }


    }

    return cmd;

}

//找到start 到 end 的最短路径
//使用引用
//bfs
int AI::canFindPath(const cube &start, const cube &end)
{
    if(start==end)
        return 0;
    QQueue<cube> bfs;
    QList<cube> visited;
    cube tmp;
    const int next[4][2] = { { snakeNodeWidth,0 } ,{ 0,snakeNodeWidth },{ -snakeNodeWidth,0 },{ 0,-snakeNodeWidth } };

    bfs.append(start);

    for(int i=0;i<snake.length()-1;i++)
    {
        visited.append(snake.at(i));
    }

    //如果终点是尾巴就把尾巴设为可走
    if(end != snake.back())
    {
        visited.append(snake.back());
    }


    while(!bfs.isEmpty())
    {
        for(int k=0;k<4;k++)
        {
            tmp.x=bfs.at(0).x + next[k][0];
            tmp.y=bfs.at(0).y + next[k][1];
            //出界
            if(snake.at(0).x<0 || snake.at(0).y<0 || snake.at(0).x>640 || snake.at(0).y>640)
                continue;

            //入队
            if(!visited.count(tmp))
            {
                tmp.step=bfs.front().step+1;
                visited.append(tmp);
                bfs.append(tmp);
            }

            if(tmp==end)
            {
                return tmp.step;
            }

        }

        bfs.pop_front();
    }

    return -1;

}

void AI::deleteLastRectF()
{
    snake.removeLast();

}
bool AI::canFindTail(cube start)
{
    return canFindPath(start,snake.back())>0 ? 1 :0;
}


bool AI::canFindFood(cube start)
{

    return canFindPath(start,food)>0 ? 1 :0;
}

int AI::nextCmdToFood()
{
   const int next[4][2] = { { snakeNodeWidth,0 } ,{ 0,snakeNodeWidth },{ -snakeNodeWidth,0 },{ 0,-snakeNodeWidth } };
    cube aroundPoint[4];
    for (int i = 0; i < 4; i++) {
                aroundPoint[i].x = snake.front().x + next[i][0];
                aroundPoint[i].y = snake.front().y + next[i][1];

                if(aroundPoint[i].x<0 || aroundPoint[i].y<0 || aroundPoint[i].x>640 || aroundPoint[i].y>640 ||onSnake_ExceptTail(aroundPoint[i]))
                      aroundPoint[i].step = -1;
                else
                    aroundPoint[i].step = canFindPath(aroundPoint[i], food);
            }

    //选最近的
    int min=0;
    for(int i=0;i<4;i++)
   {
        if (aroundPoint[i].step != -1) {
                        if (aroundPoint[i].step < aroundPoint[min].step) {
                            min = i;


                        }
        }
    }


    //返回moveflag 右0 上1 左2 下3
    //若找不到食物返回-1
    if (aroundPoint[min].step != -1)
            return min;
    else return -1;



}

int AI::nextCmdTOFarAway(const cube &start)
{
    const int next[4][2] = { { snakeNodeWidth,0 } ,{ 0,snakeNodeWidth },{ -snakeNodeWidth,0 },{ 0,-snakeNodeWidth } };
    cube aroundPoint[4];
    for (int i = 0; i < 4; i++) {
                aroundPoint[i].x = snake.front().x + next[i][0];
                aroundPoint[i].y = snake.front().y + next[i][1];

                if(canFindTail(aroundPoint[i]) && aroundPoint[i].x>=0 && aroundPoint[i].y>=0 &&aroundPoint[i].x<=640 && aroundPoint[i].y<=640 && !onSnake_ExceptTail(aroundPoint[i]))
                      aroundPoint[i].step = getManhattanDistance(aroundPoint[i],start);
                else
                    aroundPoint[i].step = -1;
            }

    //选最远的
    int max=0;
    for(int i=0;i<4;i++)
   {
        if (aroundPoint[i].step != -1) {
                        if (aroundPoint[i].step >= aroundPoint[max].step) {
                            max = i;


                        }
        }
    }

    //返回moveflag 右0 上1 左2 下3
    //若找不到食物返回-1
    if (aroundPoint[max].step != -1)
            return max;
    else return -1;

}

int AI::getManhattanDistance(cube a,cube b) {
        return abs(a.x-b.x)/snakeNodeWidth +abs(a.y-b.y/snakeNodeWidth);
    }
int AI::nextCmdTOTail()
{
    const int next[4][2] = { { snakeNodeWidth,0 } ,{ 0,snakeNodeWidth },{ -snakeNodeWidth,0 },{ 0,-snakeNodeWidth } };
    cube aroundPoint[4];
    for (int i = 0; i < 4; i++) {
                aroundPoint[i].x = snake.front().x + next[i][0];
                aroundPoint[i].y = snake.front().y + next[i][1];

                if(aroundPoint[i].x<0 || aroundPoint[i].y<0 || aroundPoint[i].x>640 || aroundPoint[i].y>640 ||onSnake_ExceptTail(aroundPoint[i]))
                      aroundPoint[i].step = -1;
                else
                    aroundPoint[i].step = canFindPath(aroundPoint[i], snake.last());
            }

    //选最远的
    int max=0;
    for(int i=0;i<4;i++)
   {
        if (aroundPoint[i].step != -1) {
                        if (aroundPoint[i].step >= aroundPoint[max].step) {
                            max = i;


                        }
        }
    }

    //返回moveflag 右0 上1 左2 下3
    //若找不到食物返回-1
    if (aroundPoint[max].step != -1)
            return max;
    else return -1;

}

bool AI::onSnake_ExceptTail(cube check) {
    if (snake.count(check) && check != snake.last()) return 1;
    else return 0;

}
*/
