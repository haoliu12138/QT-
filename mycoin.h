#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QPushButton *parent = nullptr);
    //带一个参数的构造函数 参数为图片路径
    MyCoin(QString butImg);

    int posX;
    int posY;
    bool flag;

    void changeFlag(); //改变标志执行翻转效果
    QTimer * timer1; //正面翻反面 定时器
    QTimer * timer2; //反面翻正面定时器
    int min=1; //最小的动画
    int max=8; //最大的动画

    bool isAnimation=false; //是否在做动画标志位

    void mousePressEvent(QMouseEvent * e);

    bool isWin=false;
signals:

};

#endif // MYCOIN_H
