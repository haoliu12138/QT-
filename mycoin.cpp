#include "mycoin.h"
#include<QDebug>
#include<QTimer>
MyCoin::MyCoin(QPushButton *parent) : QPushButton(parent)
{

}
MyCoin::MyCoin(QString butImg)
{
    QPixmap pix;
    bool ret=pix.load(butImg);
    if(!ret)
    {
        qDebug()<<"加载硬币图片失败"<<endl;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(this->width(),this->height()));

    //创建定时器
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    //监听计时器的信号和槽
    connect(timer1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1.png").arg(this->min++);
       pix.load(str);
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));
       if(this->min>this->max)
       {
           this->min=1;
           this->isAnimation=false;
           timer1->stop();
       }
    });
    connect(timer2,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1.png").arg((this->max)--);
       pix.load(str);
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));
       if(this->max<this->min)
       {
           this->max=8;
           this->isAnimation=false;
           timer2->stop();
       }
    });
}

void MyCoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);
        this->isAnimation=true;
        this->flag=false;
    }
    else
    {
        timer2->start(30);
        this->isAnimation=true;
        this->flag=true;
    }
}
//重写mousePressEvent防止在上个动画未结束就进行下一个动画
void MyCoin::mousePressEvent(QMouseEvent * e){
    //如果上个动画没有结束直接return 不进行后续操作
    if(this->isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}

