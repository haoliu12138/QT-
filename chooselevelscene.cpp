#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("选择关卡");
    //获取菜单栏
    QMenuBar * bar=this->menuBar();
    this->setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("开始");

    QAction * quitaction=startMenu->addAction("退出");
    //点击菜单上的退出就退出
    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });

    //在关卡选择界面创建返回按钮
    MyPushButton * backbtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    backbtn->setParent(this);
    //返回音效
    QSound * backSound=new QSound(":/res/BackButtonSound.wav");
    //关卡选择音效
    QSound  * chooseSound=new QSound(":/res/TapButtonSound.wav");
    //设置返会按钮点击后隐藏选择界面并且触发自定义信号来重新显示开始界面
    connect(backbtn,&MyPushButton::clicked,[=](){
       backSound->play();
       this->hide(); 
       //触发自定义信号
       emit this->chooseSenseBack();
    });
    //创建关卡选择按钮
    for(int i=0;i<20;i++)
    {
        //创建选择关卡按钮
        MyPushButton * menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);
        //创建选择按钮上显示的关卡标签
        QLabel * label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->width());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter); //设置水平以及垂直居中
        label->move(25+(i%4)*70,130+(i/4)*70); //把标签移动到按钮的位置上
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true); //鼠标事件穿透 穿过标签点到按钮注释之后点不到按钮了

        //监听选择关卡的按钮的信号
        connect(menuBtn,&MyPushButton::clicked,[=]()
        {
           if(playScene==NULL){
               chooseSound->play();
               this->hide();//隐藏关卡选择界面
               playScene=new PlayScene(i+1);//将选择的关卡号传给 游戏界面的构造函数
               playScene->setGeometry(this->geometry());
               playScene->show();
               //play界面的返回按钮的信号
               connect(playScene,&PlayScene::chooseSenseBack,[=](){
                   //重新显示关卡选择界面
                   this->setGeometry(playScene->geometry());
                   this->show();
                   //释放堆空间上的内存
                   delete(playScene);
                   playScene=NULL;
               });

           }
        });

    }
}
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

