#ifndef COINFLIP_H
#define COINFLIP_H

#include <QMainWindow>
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CoinFlip; }
QT_END_NAMESPACE

class CoinFlip : public QMainWindow
{
    Q_OBJECT

public:
    CoinFlip(QWidget *parent = nullptr);
    ~CoinFlip();

    void paintEvent(QPaintEvent *);
    //创建关卡选择界面
    ChooseLevelScene * choose =new ChooseLevelScene();
private:
    Ui::CoinFlip *ui;
};
#endif // COINFLIP_H
