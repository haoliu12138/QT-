#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    PlayScene * playScene=NULL;
signals:
    //定义点击返回按钮的信号
    void chooseSenseBack();

};

#endif // CHOOSELEVELSCENE_H
