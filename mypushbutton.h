#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //提供重载版本的构造函数
    MyPushButton(QString normalImg,QString pressImg="");
    //按钮跳跃特效函数
    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);


    QString normalImgPath; //默认显示图片路径
    QString pressImgPath; //按下后显示的图片的路径

signals:

};

#endif // MYPUSHBUTTON_H
