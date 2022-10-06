#include "coinflip.h"
#include "ui_coinflip.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSound>
CoinFlip::CoinFlip(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CoinFlip)
{
    ui->setupUi(this);
    //设置界面大小
    this->setFixedSize(320,588);
    //设置窗口左上角图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("CoinFlip");
    //点击退出退出程序
    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });
    //创建按钮类
    MyPushButton * mybtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    //将按钮放到窗口中
    mybtn->setParent(this);
    //移动按钮的到窗口中间靠下位置处
    mybtn->move(this->width()*0.5-mybtn->width()*0.5,this->height()*0.7);
    //开始音效
    QSound * startSound=new QSound(":/res/TapButtonSound.wav");
    //给mybtn 连接信号和槽
    connect(mybtn,&MyPushButton::clicked,[=](){
        startSound->play();
        mybtn->zoom1();
        mybtn->zoom2();
        //延时0.5秒后显示选择界面
        QTimer::singleShot(500,this,[=](){
            //隐藏开始界面
            this->hide();
            choose->setGeometry(this->geometry());
            //显示关卡选择界面
            choose->show();
        });
    });
    //这里连接选择关卡的chooseSenseBack信号，这个信号由返回按钮触发，返回按钮触发信号后重新显示主界面
    connect(choose,&ChooseLevelScene::chooseSenseBack,[=](){
        this->setGeometry(choose->geometry());
        this->show();
    });
}

CoinFlip::~CoinFlip()
{
    delete ui;
}
//绘图事件在窗口出现时就会执行，所以可以直接画出界面
void CoinFlip::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmao
    QPixmap pix;
    //从资源中加载文件
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景图片上的小标题图片
    pix.load(":/res/Title.png");
    //缩小图片
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //把图片画上去
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
