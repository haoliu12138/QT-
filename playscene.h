#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    //带一个参数的构造函数
    PlayScene(int index);
    //paintEvent
    void paintEvent(QPaintEvent *);
    //成员变量 记录关卡索引
    int levalIndex;
    //记录当前关卡的二位数组
    int gameArray[4][4];
    //定义金币数组
    MyCoin * coinBtn[4][4];
    //胜利标志位
    bool isWin;
signals:
    //定义点击返回按钮的信号
    void chooseSenseBack();



};

#endif // PLAYSCENE_H
