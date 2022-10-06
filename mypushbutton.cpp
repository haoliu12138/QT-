#include "mypushbutton.h"
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>
//构造函数
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    normalImgPath=normalImg;
    pressImgPath=pressImg;
    //创建QPixmap对象
    QPixmap pix;
    //判断能否加载正常显示的图片
    bool ret=pix.load(normalImgPath);
    if(!ret)
    {
        qDebug()<<"加载图片失败";
    }
    //设置按钮的大小和图片大小一样
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置按钮的图标
    this->setIcon(pix);
    //设置按钮内的图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
//特效函数
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation1=new QPropertyAnimation(this,"geometry");
    //设置时间间隔,单位毫秒
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}
void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation1=new QPropertyAnimation(this,"geometry");
    //设置时间间隔,单位毫秒
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{

    if(normalImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(normalImgPath);
        if(!ret)
        {
            qDebug()<<"加载正常图片失败"<<endl;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(pressImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(pressImgPath);
        if(!ret)
        {
            qDebug()<<"加载按下图片失败:"<<pressImgPath<<endl;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
