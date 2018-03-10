#include "widget.h"
#include "hiLabel.h"
#include <QGridLayout>
#include "lrcLabel.h"
#include "hiVolBotton.h"
//#include <QPixmap>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    hiButton=new HiButton;

    hiButton->hi_setButtonIcons(QIcon(":/hiPlayer/resources/播放按钮-主界面.png"),QIcon(":/hiPlayer/resources/播放按钮-主界面2.png"),QIcon(":/hiPlayer/resources/暂停按钮-主界面2.png"));
    QGridLayout * mainLayout=new QGridLayout;
    mainLayout->addWidget(hiButton);
    setLayout(mainLayout);

    HiLabel * label=new HiLabel;
    label->hi_setText("问君此去几时还,来时莫徘徊",600);

    mainLayout->addWidget(label);

    HiVolBotton * volBtn=new HiVolBotton;
    mainLayout->addWidget(volBtn);

    connect(volBtn,SIGNAL(hi_volumeChanged(int)),this,SLOT(slotVolChange(int)));

//    LrcLabel lrcLabel;
//    lrcLabel.hi_setText("问君此去几时还,来时莫徘徊");
//    lrcLabel.hi_startLrcMask(1000);
//    mainLayout->addWidget(&lrcLabel);
}

Widget::~Widget()
{

}

void Widget::slotVolChange(int vol)
{
    qDebug()<<"vol change:"<<vol;
}

void Widget::slotRecvMessage(QString message)
{
    qDebug()<<"Tips:"<<message;
    this->showNormal();
    this->raise();
    this->activateWindow();
}
