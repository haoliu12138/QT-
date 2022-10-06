#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QLabel>
#include<QTimer>
#include<QDebug>
#include "mypushbutton.h"
#include "dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}
PlayScene::PlayScene(int index)
{
    this->levalIndex=index;

    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("翻金币");

    QMenuBar * menuBar= this->menuBar();
    this->setMenuBar(menuBar);

    QMenu * menu=menuBar->addMenu("开始");

    QAction * exitAction=menu->addAction("退出");

    connect(exitAction,&QAction::triggered,[=](){
        this->close();
    });

    //在关卡选择界面创建返回按钮
    MyPushButton * backbtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    backbtn->setParent(this);
    //返回音效
    QSound * backSound=new QSound(":/res/BackButtonSound.wav");
    //翻金币音效
    QSound * flipSound=new QSound(":/res/ConFlipSound.wav");
    //胜利音效
    QSound * winSound=new QSound(":/res/LevelWinSound.wav");

    //设置返会按钮点击后隐藏选择界面并且触发自定义信号来重新显示开始界面
    connect(backbtn,&MyPushButton::clicked,[=](){
       backSound->play();
       this->hide();
       //触发自定义信号
       emit this->chooseSenseBack();
    });
    //当前关卡标题
    QLabel * label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str=QString("Leavel:%1").arg(this->levalIndex);
    label->setText(str);
    //设置label标签位置以及边框大小
    label->setGeometry(QRect(30,this->height()-50,140,50));
    //引入关卡数据
    dataConfig config;
    //创建金币的背景图片,和初始化关卡
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制背景图片
            QLabel * label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            //初始化关卡数据数组
            int node;
            QString img;
            node=config.mData[levalIndex][i][j];

            gameArray[i][j]=node;
            if(node==1)
            {
                img=":/res/Coin0001.png";
            }else
            {
                img=":/res/Coin0008.png";
            }

            //在背景图片上绘制金币
            MyCoin * myCoin=new MyCoin(img);
            myCoin->setParent(this);
            myCoin->move(59+i*50,204+j*50);
            //记录硬币信息
            myCoin->posX=i;//x坐标
            myCoin->posY=j;//y坐标
            myCoin->flag=node;//正反标志位
            //把新建的金币存放到金币数组中
            coinBtn[i][j]=myCoin;
            //准备好胜利的图片(这个不能写到连接的lambda表达式里)
            QLabel * winLabel=new QLabel;
            QPixmap pix;
            pix.load(":/res/LevelCompletedDialogBg.png");
            winLabel->setGeometry(0,0,pix.width(),pix.height());
            winLabel->setPixmap(pix);
            //放到窗口外 y坐标为负数
            winLabel->move((this->width()-pix.width())*0.5,-pix.height());
            winLabel->setParent(this);
            //连接金币的点击信号
            connect(myCoin,&MyCoin::clicked,[=](){
                flipSound->play();
                myCoin->changeFlag();
                //这个意思就是把对应的数组中的数据置反 原来是0就置为1 反之亦然
                gameArray[i][j]=gameArray[i][j]==0?1:0;
                //翻完点击的金币后延时翻周围的金币
                QTimer::singleShot(300,[=](){
                    //判断右边是否可以翻转
                    if(myCoin->posX+1<=3)
                    {
                        coinBtn[myCoin->posX+1][myCoin->posY]->changeFlag();
                        gameArray[myCoin->posX+1][myCoin->posY]=gameArray[myCoin->posX+1][myCoin->posY]==0?1:0;
                    }
                    //判断左边是否可以翻转
                    if(myCoin->posX-1>=0)
                    {
                        coinBtn[myCoin->posX-1][myCoin->posY]->changeFlag();
                        gameArray[myCoin->posX-1][myCoin->posY]=gameArray[myCoin->posX-1][myCoin->posY]==0?1:0;
                    }
                    //判断下面是否可以翻转
                    if(myCoin->posY+1<=3)
                    {
                        coinBtn[myCoin->posX][myCoin->posY+1]->changeFlag();
                        gameArray[myCoin->posX][myCoin->posY+1]=gameArray[myCoin->posX][myCoin->posY+1]==0?1:0;
                    }
                    //判断上面是否可以翻转
                    if(myCoin->posY-1>=0)
                    {
                        coinBtn[myCoin->posX][myCoin->posY-1]->changeFlag();
                        gameArray[myCoin->posX][myCoin->posY-1]=gameArray[myCoin->posX][myCoin->posY-1]==0?1:0;
                    }
                    //翻完金币后判断是否胜利 所有金币都为正面即为胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(gameArray[i][j]==0)
                            {
                               this->isWin=false;
                               break;
                            }
                        }
                    }
                    if(this->isWin)
                    {
                        winSound->play();
                        qDebug()<<"胜利"<<endl;
                        QPropertyAnimation * animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                        //禁用所有按钮点击事件
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                    }

                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
